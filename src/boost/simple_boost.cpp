#define BOOST_ALLOW_DEPRECATED_HEADERS

#include <boost/numeric/odeint.hpp>
#include <vector>

using namespace boost::numeric::odeint;

/* The type of container used to hold the state vector */
typedef std::vector<double> state_type;

const double gam = 0.15;

/* The rhs of x' = f(x) */
void harmonic_oscillator(const state_type &x, state_type &dxdt, const double /* t */) {
    dxdt[0] = x[1];
    dxdt[1] = -x[0] - gam * x[1];
}

// An example of observer to record steps in the integration
struct push_back_state_and_time {
    std::vector<state_type> &m_states;
    std::vector<double> &m_times;

    push_back_state_and_time(std::vector<state_type> &states, std::vector<double> &times)
            : m_states(states), m_times(times) {}

    void operator()(const state_type &x, double t) {
        m_states.push_back(x);
        m_times.push_back(t);
    }
};

int main() {

    // Containers to store solution
    std::vector<state_type> x_vec;
    std::vector<double> times;

    // Unknown variables with initial conditions
    state_type x(2);
    x[0] = 1.0; // start at x=1.0, p=0.0
    x[1] = 0.0;

    // Integration process. Returns the number of performed steps. This one determines
    // the stepper automatically.
//    auto steps = integrate(harmonic_oscillator,
//                           x, 0.0, 10.0, 0.1,
//                           push_back_state_and_time(x_vec, times));

    // Or you can choose it explicitly
    runge_kutta4<state_type> stepper;
    auto steps = integrate_const(
            stepper,
            harmonic_oscillator,
            x,
            0.0,
            10.0,
            0.1,
            push_back_state_and_time(x_vec, times));

    /* output */
    for (size_t i = 0; i <= steps; i++) {
        std::cout << times[i] << '\t' << x_vec[i][0] << '\t' << x_vec[i][1] << '\n';
    }

    std::cout << "\n*******************\n\n";

    // Or, for a finer control, each step can be performed explicitly as below
    const auto dt = 0.1;
    const auto t0 = 0.0;
    const auto tfinal = 10.0;
    state_type x_explicit(2);
    x_explicit[0] = 1.0; // start at x=1.0, p=0.0
    x_explicit[1] = 0.0;
    std::cout << 0 << '\t' << x_explicit[0] << '\t' << x_explicit[1] << '\n';
    for (double t = t0 + dt; t < tfinal; t +=dt){
        stepper.do_step(harmonic_oscillator, x_explicit, t, dt);
        std::cout << t << '\t' << x_explicit[0] << '\t' << x_explicit[1] << '\n';
    }

    return 0;
}