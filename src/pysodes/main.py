import numpy as np

from src.pysodes.odeint import solve_ivp_wrapper


def lorenz(x, dxdt, t):
    sigma = 10.0
    R = 28.0
    b = 8.0 / 3.0

    dxdt[0] = sigma * (x[1] - x[0])
    dxdt[1] = R * x[0] - x[1] - x[0] * x[2]
    dxdt[2] = -b * x[2] + x[0] * x[1]

    return dxdt


t_span = (0., 10.)
dt = 0.01
y0 = np.array([0., 1., 0.1])

time, solution = solve_ivp_wrapper(lorenz, t_span, dt, y0)
print(solution[-1])
