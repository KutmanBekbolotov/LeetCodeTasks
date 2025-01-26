import numpy as np
import matplotlib.pyplot as plt

# Gravitational constant and mass of the central body
G = 6.67430e-11  # m³/(kg·s²)
M = 1.989e30     # mass of the central body (e.g., Sun), kg

# Initial conditions
x0 = 1.5e11      # initial position of the star along the x-axis, m (about 1 AU)
y0 = 0           # initial position along the y-axis, m
vx0 = 0          # initial velocity along the x-axis, m/s
vy0 = 3e4        # initial velocity along the y-axis, m/s (approx Earth's orbital speed)

# Time parameters
dt = 60          # time step, seconds
steps = 10000    # number of simulation steps

# Arrays to store position and velocity
x = np.zeros(steps)
y = np.zeros(steps)
vx = np.zeros(steps)
vy = np.zeros(steps)

# Set initial values
x[0], y[0] = x0, y0
vx[0], vy[0] = vx0, vy0

# Simulation loop
for i in range(steps - 1):