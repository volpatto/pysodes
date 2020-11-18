import pytest
from pytest import approx
import numpy as np
from scipy.integrate import solve_ivp

from pysodes.odeint import integrate_const


def lotka_volterra(z, dzdt, t):
    x, y = z

    a = 1.5
    b = 1.0
    c = 3.0
    d = 1.0

    dzdt[0] = a*x - b*x*y
    dzdt[1] = -c*y + d*x*y

    return dzdt


def lotka_volterra_scipy(t, z):
    x, y = z

    a = 1.5
    b = 1.0
    c = 3.0
    d = 1.0

    dxdt = [
        a*x - b*x*y,
        -c*y + d*x*y
    ]
    return dxdt


def lorenz(x, dxdt, t):
    sigma = 10.0
    R = 28.0
    b = 8.0 / 3.0

    dxdt[0] = sigma * (x[1] - x[0])
    dxdt[1] = R * x[0] - x[1] - x[0] * x[2]
    dxdt[2] = -b * x[2] + x[0] * x[1]

    return dxdt


def lorenz_scipy(t, y):
    x = y

    sigma = 10.0
    R = 28.0
    b = 8.0 / 3.0

    dxdt_0 = sigma * (x[1] - x[0])
    dxdt_1 = R * x[0] - x[1] - x[0] * x[2]
    dxdt_2 = -b * x[2] + x[0] * x[1]

    return dxdt_0, dxdt_1, dxdt_2


@pytest.mark.parametrize("odeint_method, rtol", [
    ["runge_kutta4", 4e-3],
    ["runge_kutta_cash_karp54", 4e-3],
    ["runge_kutta_fehlberg78", 4e-3],
    # This relative error is expected, since midpoint is
    # a poor quality method and the problem is stiff
    ["modified_midpoint", 2e-2],
])
def test_compare_regular_steppers_with_scipy_lv(odeint_method, rtol):
    t_span = (0., 10.)
    dt = 0.01
    num_of_steps = int((t_span[1] - t_span[0]) / dt) + 1
    t_eval_scipy = np.linspace(t_span[0], t_span[1], num_of_steps)
    y0 = np.array([10., 5.])

    _, solution_odeint = integrate_const(lotka_volterra, t_span, dt, y0, method=odeint_method)

    result = solve_ivp(lotka_volterra_scipy, t_span, y0, t_eval=t_eval_scipy, method='Radau')
    solution_scipy = result.y.T

    assert solution_odeint == approx(solution_scipy, rel=rtol)


@pytest.mark.parametrize("odeint_method, rtol", [
    ["runge_kutta4", 7e-3],
    ["runge_kutta_cash_karp54", 7e-3],
    ["runge_kutta_fehlberg78", 7e-3],
    # This relative error is expected, since midpoint is
    # a poor quality method and the problem is stiff
    ["modified_midpoint", 7e-2],
])
def test_compare_regular_steppers_with_scipy_lorenz(odeint_method, rtol):
    t_span = (0., 10.)
    dt = 0.01
    num_of_steps = int((t_span[1] - t_span[0]) / dt) + 1
    t_eval_scipy = np.linspace(t_span[0], t_span[1], num_of_steps)
    y0 = np.array([0., 1., 0.1])

    _, solution_odeint = integrate_const(lorenz, t_span, dt, y0, method=odeint_method)

    result = solve_ivp(lorenz_scipy, t_span, y0, t_eval=t_eval_scipy, method='Radau')
    solution_scipy = result.y.T

    assert solution_odeint == approx(solution_scipy, rel=rtol)
