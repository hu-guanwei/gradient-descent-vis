### Gradient Descent Visualization

#### Capstone Option 1

This is a 2d gradient descent algorithm simulator where multiple balls with possibly different initial positions are rolling down the landscape surface. The background brightness indicate the landscape surface value: The darker, the lower. The balls will go from random initial positions towards the position of lowest landscape surface value. Multi-threading is used to concurrently display and update positions of balls.

Library `opencv` is needed.

#### Running the code

- To compile the code
  `mkdir build && cd build`
  `cmake ..`
  `make`

- To start the application GUI, run`./gradient_descent_viz`

  - When the GUI is running:

    - press key `q` to quit the GUI. (The simulation is still running with printing to console. `CTRL+C` to stop the simulation)

    - press key `r` to reset the positions of balls randomly. 

#### Code structure
- `src/Graphics.h/Graphics.cpp`: display landscape surface and balls position
- `src/Ball.h/Ball.cpp`: update the position of a ball by going along the gradient of landscape surface 

#### Rubric

##### Object Oriented Programming

| Criteria                                                     | Meets Specifications                                         | files                                                  |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------ |
| The project uses Object Oriented Programming techniques.     | The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks. | see `Ball.h`, `Ball.cpp`,` Graphics.h`, `Graphics.cpp` |
| Classes use appropriate access specifiers for class members. | All class data members are explicitly specified as public, protected, or private. | see `Ball.h`, `Graphics.h`                             |



##### Memory Management

| Criteria                                                     | Meets Specifications                                         | files and line numbers                                       |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| The project makes use of references in function declarations. | At least two variables are defined as references, or two functions use pass-by-reference in the project code. | `Ball.cpp` line 10, `main.cpp` line 35; `Graphics.cpp` line 55 |
| The project uses smart pointers instead of raw pointers.     | The project uses at least one smart pointer: `unique_ptr`, `shared_ptr`, or `weak_ptr`. The project does not use raw pointers. | `std::vector<std::shared_ptr<Ball>> _balls` in `Graphics.h` line 14 |

In `Ball.cpp` line 10

```c++
void Ball::simulate(std::mutex &mu)
```

In `main.cpp` line 35

```c++
	ts.emplace_back(&Ball::simulate, b, std::ref(mu));
```

In `Graphics.cpp` line 55

```c++
void Graphics::fillLandscapeWith(const std::function<float(float, float)> &f)
```



##### Concurrency

| Criteria                               | Meets Specifications                                         | files and line numbers |
| -------------------------------------- | ------------------------------------------------------------ | ---------------------- |
| The project uses multithreading        | The project uses multiple threads in the execution.          | `main.cpp` line 33-36  |
| A mutex or lock is used in the project | A mutex or lock (e.g. `std::lock_guard` or `std::unique_lock)  is used to protect data that is shared across multiple threads in the project code. | `Ball.cpp` line 28-34  |

In `main.cpp`

```c++
33    for (auto &b: balls) {
34        // simulate each ball in a different thread
35        ts.emplace_back(&Ball::simulate, b, std::ref(mu));
36    }
```

In `Ball.cpp`

```c++
28      mu.lock(); 
29      std::cout << "thread id\t: ";
30      std::cout << std::this_thread::get_id() << std::endl;
31      std::cout << "gradient norm\t: ";
32      std::cout << sqrt(pow(dx, 2) + pow(dy, 2)) << std::endl; 
33      std::cout << "===================================" << std::endl;
34      mu.unlock();   
```

This is to ensure console outputs will not be interleaved. (The variable`std::mutex mu` is defined in `main.cpp`.)
