from typing import Callable, Union, List, Tuple
import numpy as np
from src.pysodes._bindings.sodes_bindings import solve_ivp_odeint


def solve_ivp_wrapper(
    f: Callable,
    t_span: Tuple,
    dt: float,
    y0: np.ndarray,
    method: str = 'runge_kutta4'
):
    return solve_ivp_odeint(f, t_span, dt, y0, method)

