# pysODEs

Testing C++ ODE solvers wrapping to Python. Really **early stage (WORK-IN-PROGRESS)** project.

The idea is to design a header-only thin wrapper for some (not all, actually very few) [Boost::odeint](https://headmyshoulder.github.io/odeint-v2/),
[GNU Scientific Library](https://www.gnu.org/software/gsl/doc/html/ode-initval.html) and
[Sundials' CVODE](https://computing.llnl.gov/projects/sundials) solvers. Everything here is quite
experimental and my main goal is to learn and improve my hybrid C++/Python code development and
bindings techniques.

**P.S.:** `pysODEs` is the bindings for `sODEs`, which is the C++ code part. And `sODEs` means
"solvers for Ordinary Differential Equations systems". ;)

## Contact

My name is Diego. My email is dtvolpatto@gmail.com.
