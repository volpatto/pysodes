from typing import Callable, Tuple
import numpy as np
from src.pysodes._bindings.sodes_bindings import solve_ivp_odeint


def solve_ivp_wrapper(
    f: Callable,
    t_span: Tuple,
    dt: float,
    y0: np.ndarray,
    method: str = 'runge_kutta4'
) -> Tuple[np.ndarray, np.ndarray]:
    """
    A Python wrapper for Boost::odeint runge_kutta4 (the only one supported right now)
    stepper and ODE integration.

    :param f:
        The ODE system RHS.

    :param t_span:
        The time range in which integration is performed. It is provided as
        (t_initial, t_final) tuple.

    :param dt:
        The time-step to increment time from t_span[0] to t_span[1].

    :param y0:
        Initial conditions for the system state.

    :param method:
        The stepper method. Only 'runge_kutta4' is supported at the moment.

    :return:
        A tuple with two arrays: (time, solution). The first contains the time points
        from integration and the last is a matrix with the solution for each state provided
        by columns. In other words, solution[:, 0] contains the solution for state 0,
        solution[:, 1] for state 1 and so forth.
    """
    time, solution = solve_ivp_odeint(f, t_span, dt, y0, method)
    solution = np.array(solution)
    time = np.array(time)
    return time, solution

