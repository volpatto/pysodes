#include <boost/numeric/odeint.hpp>
#include <boost/array.hpp>
#include <vector>

using namespace boost::numeric::odeint;

/* The type of container used to hold the state vector */
typedef boost::array<double, 3> state_type;

void lorenz(const state_type &x, state_type &dxdt, const double t) {
    double sigma = 10.0;
    double R = 28.0;
    double b = 8.0 / 3.0;

    dxdt[0] = sigma * (x[1] - x[0]);
    dxdt[1] = R * x[0] - x[1] - x[0] * x[2];
    dxdt[2] = -b * x[2] + x[0] * x[1];
}

// An example of observer to record steps in the integration
struct boost_array_observer {
    std::vector<state_type> &m_states;
    std::vector<double> &m_times;

    boost_array_observer(std::vector<state_type> &states, std::vector<double> &times)
            : m_states(states), m_times(times) {}

    void operator()(const state_type &x, double t) {
        m_states.push_back(x);
        m_times.push_back(t);
    }
};

int main() {
    // this time, let the num of steps be known
    const auto n_steps = 1000;

    // System state initialization with initial condition
    state_type x = {0.0, 1.0, 0.1};

    // Containers to store solution
    std::vector<state_type> x_sol;
    std::vector<double> times;

    // Set stepper
    runge_kutta4<state_type> rk4;

    // Integrate over time
    auto t_init = 0.0;
    auto t_final = 10.0;
    auto dt = 0.001;
    auto steps = integrate_const(
            rk4,
            lorenz,
            x,
            t_init,
            t_final,
            dt,
            boost_array_observer(x_sol, times)
    );

    // Displaying result on terminal
    for (size_t i = 0; i <= steps; i++) {
        std::cout << times[i] << '\t' << x_sol[i][0] << '\t' << x_sol[i][1] << '\t' << x_sol[i][2] << '\n';
    }

    return 0;
}
