from invoke import task
from invoke.exceptions import Exit
from pathlib import Path
from typing import Optional
import os
import shutil
import sys

BUILD_DIR_DEFAULT = Path(os.environ['BUILD_DIR'].replace(":", ""))


def _get_vcvars_paths():
    template = r"%PROGRAMFILES(X86)%\Microsoft Visual Studio\2017\{edition}\VC\Auxiliary\Build\vcvarsall.bat"
    template = os.path.expandvars(template)
    editions = ('BuildTools', 'Professional', 'WDExpress', 'Community')
    return tuple(Path(template.format(edition=edition)) for edition in editions)


def strip_and_join(s: str):
    return ' '.join(line.strip() for line in s.splitlines() if line.strip() != '')


def echo(c, msg: str):
    from colorama.ansi import Fore, Style
    if c.config.run.echo:
        print(f"{Fore.WHITE}{Style.BRIGHT}{msg}{Style.RESET_ALL}")


def remove_directory(path: Path):
    if path.is_dir():
        print(f"Removing {path}")
        shutil.rmtree(path)
    else:
        print(f"Not removing {path} (not a directory)")


def _get_and_prepare_build(
        c,
        clean: bool = False,
        build_subdirectory: Path = BUILD_DIR_DEFAULT
) -> Path:
    '''
    Returns build directory where `cmake` shall be called from. Creates it and
    possibly removes its contents (and artifacts_dir contents) if `clean=True`
    is passed.
    '''
    build_dir = build_subdirectory
    if clean:
        remove_directory(build_dir)
    build_dir.mkdir(parents=True, exist_ok=not clean)
    return build_dir


def _get_cmake_command(
        build_dir: Path,
        cmake_generator: str,
        cmake_arch: Optional[str] = None,
        config: str = 'Release',
):
    '''
    :param build_dir: Directory from where cmake will be called.
    '''
    root_dir = Path(__file__).parent
    relative_root_dir = Path(os.path.relpath(root_dir, build_dir))
    relative_artifacts_dir = Path(os.path.relpath(build_dir))

    return strip_and_join(f"""
        cmake
            -G "{cmake_generator}"
            {f'-A "{cmake_arch}"' if cmake_arch is not None else ""}
            -DCMAKE_BUILD_TYPE={config}
            -DCMAKE_INSTALL_PREFIX="{relative_artifacts_dir.as_posix()}"
            "{str(relative_root_dir)}"
    """)


def _get_wrappers_command(wrappers_dir: Path) -> str:
    conda_prefix = os.environ['CONDA_PREFIX']
    if sys.platform.startswith('win'):
        autodiff_env_path = f"{conda_prefix}\\Library\\bin"
    else:
        autodiff_env_path = f"{conda_prefix}/bin"
    return strip_and_join(f"""
        create-wrappers
            -t conda
            --bin-dir {autodiff_env_path}
            --dest-dir {wrappers_dir}
            --conda-env-dir {conda_prefix}
    """)


def _get_test_command():
    test_command = strip_and_join(f"""
        pytest .
            -n auto
    """)
    return test_command


if sys.platform.startswith('win'):
    @task
    def msvc(c, clean=False, config='Release'):
        """
        Generates a Visual Studio project at the "build/msvc" directory.
        Assumes that the environment is already configured using:
            conda devenv
            activate env_name_here
        """
        build_dir, artifacts_dir = _get_and_prepare_build(
            c,
            clean=clean,
            build_subdirectory=BUILD_DIR_DEFAULT / "msvc",
        )
        cmake_command = _get_cmake_command(build_dir=build_dir, cmake_generator="Visual Studio 15 2017",
                                           cmake_arch="x64", config=config)
        os.chdir(build_dir)
        c.run(cmake_command)


@task
def compile(c, clean=False, config='Release', number_of_jobs=-1, gen_wrappers=False):
    """
    Compiles by running CMake and building with `ninja`.
    Assumes that the environment is already configured using:
        conda devenv
        [source] activate env_name
    """
    build_dir = _get_and_prepare_build(
        c,
        clean=clean,
        build_subdirectory=BUILD_DIR_DEFAULT,
    )

    cmake_command = _get_cmake_command(build_dir=build_dir, cmake_generator="Ninja", config=config)
    build_command = strip_and_join(f"""
        cmake
            --build .
            --target install
            --config {config}
            --
                {f"-j {number_of_jobs}" if number_of_jobs >= 0 else ""}
                {"-d keeprsp" if sys.platform.startswith("win") else ""}
    """)

    commands = [cmake_command, build_command]
    if gen_wrappers:
        wrappers_command = _get_wrappers_command(build_dir / "wrappers/conda")
        commands.append(wrappers_command)

    if sys.platform.startswith('win'):
        for vcvars_path in _get_vcvars_paths():
            if not vcvars_path.is_file():
                continue
            commands.insert(0, f'"{vcvars_path}" amd64')
            break
        else:
            raise Exit(
                'Error: Commands to configure MSVC environment variables not found.',
                code=1,
            )

    os.chdir(build_dir)
    c.run("&&".join(commands))


@task
def clear(c, build_dir_path=BUILD_DIR_DEFAULT):
    """
    Clear build directory
    """
    remove_directory(build_dir_path)


@task
def wrappers(c, wrappers_dir=BUILD_DIR_DEFAULT / "wrappers/conda"):
    """
    Wrappers bin generated by conda environment as passed with --wrappers-dir dir_path
    """
    remove_directory(wrappers_dir)
    if sys.platform.startswith('win'):
        print(f"Generating conda wrappers to {wrappers_dir} from {os.environ['CONDA_PREFIX']}\\Library\\bin")
    else:
        print(f"Generating conda wrappers to {wrappers_dir} from {os.environ['CONDA_PREFIX']}/bin")

    generate_wrappers_command = _get_wrappers_command(wrappers_dir)
    echo(c, generate_wrappers_command)
    c.run(generate_wrappers_command, pty=True, warn=True)


@task
def tests(c):
    """
    Execute tests in pytest, if any
    """
    test_command = _get_test_command()
    c.run(test_command, pty=True)
