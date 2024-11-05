import numpy as np
import matplotlib.pyplot as plt

# Function to read coordinates from 'data.txt'
def read_coordinates(filename='data.txt'):
    coordinates = {}
    with open(filename, 'r') as file:
        for line in file:
            line = line.strip()  # Remove any leading/trailing whitespace
            if line:  # Skip empty lines
                try:
                    point, coords = line.split(' ', 1)  # Split into point and coordinates
                    coords = coords.strip('()')  # Remove parentheses
                    x, y = map(float, coords.split(','))  # Split by ',' and convert to floats
                    coordinates[point] = np.array([x, y]).reshape(-1, 1)
                except ValueError as e:
                    print(f"Error processing line: {line}. Error: {e}")
    return coordinates

# Read triangle vertices from 'data.txt'
vertices = read_coordinates()

# Check if vertices were read correctly
if not vertices:
    print("No vertices found. Exiting.")
    exit()

# Extract points A, B, and C from the vertices
A = vertices['A']
B = vertices['B']
C = vertices['C']

# Function to generate the line between two points
def line_gen(P, Q):
    return np.hstack((P, Q))

# Generate lines for the triangle sides
x_AB = line_gen(A, B)
x_BC = line_gen(B, C)
x_CA = line_gen(C, A)

# Plotting the triangle sides
plt.plot(x_AB[0, :], x_AB[1, :], label='AB')
plt.plot(x_BC[0, :], x_BC[1, :], label='BC')
plt.plot(x_CA[0, :], x_CA[1, :], label='CA')

# Scatter plot of the vertices
plt.scatter(A[0], A[1], color='red', zorder=5)
plt.scatter(B[0], B[1], color='red', zorder=5)
plt.scatter(C[0], C[1], color='red', zorder=5)

# Label the vertices with coordinates
plt.text(A[0] + 0.1, A[1], f'A {A.flatten()}', fontsize=12, ha='center')
plt.text(B[0] + 0.1, B[1], f'B {B.flatten()}', fontsize=12, ha='center')
plt.text(C[0] + 0.1, C[1], f'C {C.flatten()}', fontsize=12, ha='center')

# Set equal scaling and labels
plt.axis('equal')
plt.xlabel('x')
plt.ylabel('y')
plt.grid(True)
plt.legend()
plt.title('Triangle ABC with Coordinates')

# Show the plot
plt.show()

