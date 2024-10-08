import matplotlib.pyplot as plt

# Read points from data.txt
points = []
try:
    with open("data.txt", "r") as file:
        for line in file:
            line = line.strip()  # Remove whitespace
            if line:  # Check if the line is not empty
                # Strip parentheses and split by comma
                line = line.strip('()')
                x, y = map(float, line.split(','))
                points.append((x, y))
except FileNotFoundError:
    print("data.txt not found. Please make sure the file is in the correct directory.")
    exit(1)
except ValueError as e:
    print(f"Error processing line '{line}': {e}")
    exit(1)

# Unzip the points into x and y coordinates
if points:  # Only proceed if we have points
    x_coords, y_coords = zip(*points)

    # Create a new figure
    plt.figure()

    # Plot the triangle by connecting the points
    plt.plot(x_coords + (x_coords[0],), y_coords + (y_coords[0],), marker='o')  # Close the triangle

    # Define labels for points A, B, and C
    labels = ['A', 'B', 'C']
    colors = ['blue', 'green', 'red']  # Different colors for A, B, and C

    # Annotate the points with labels and coordinates
    for (x, y), label, color in zip(points, labels, colors):
        plt.text(x, y, f'{label} ({x}, {y})', fontsize=9, ha='right', color=color)

    # Set x and y axis limits
    plt.xlim(-1, 4)  # Adjust as needed
    plt.ylim(-1, 5)  # Adjust as needed

    # Set labels and title
    plt.xlabel('X coordinates (cm)')
    plt.ylabel('Y coordinates (cm)')
    plt.title('Right Triangle with Vertices A, B, C from data.txt')

    # Add grid for better visibility
    plt.grid(True)

    # Show the plot
    plt.axhline(0, color='black', linewidth=0.5, ls='--')  # Add x-axis
    plt.axvline(0, color='black', linewidth=0.5, ls='--')  # Add y-axis
    plt.show()
else:
    print("No valid points to plot.")

