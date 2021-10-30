# Overview

This repository contains an implementation of [John Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) in order to illustrate [test-driven development](https://en.wikipedia.org/wiki/Test-driven_development). Test-driven development is a software engineering methodology where test cases are created based upon requirements *prior to writing code*. John Conway's Game of Life is a cellular autmaton devised upon 4 rules.
* Any live cell with fewer than two live neighbours dies, as if by underpopulation.
* Any live cell with two or three live neighbours lives on to the next generation.
* Any live cell with more than three live neighbours dies, as if by overpopulation.
* Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

These 4 rules create an environment condusive for adopting a test-driven development methodology. A test-drive development approach typically involves the following process:
* Write a test before any code is written that passes iff the feature's specifications are met.
* Execute the tests. (The tests should fail because the code has not been written yet.)
* Write the code that causes the test  to pass.
* Execute the tests and verify the test now passes.
* Refactor and repeat.

In my experience, simply adding unit tests can tremendously increase the robustness of the code, while also influencing the design so that the objects are better defined. In this specific example, I discovered several errors in my code  as I began exercising the classes and their respective methods. 

The incorporation of tests from the beginning of design oftentimes makes developers more concise in their class definitions, as additional code and functinoality can require the overhead of additional tests. Test-driven development should cause a myriad of questions to surface such as:
* Encapsulation and prefering protected or private. Additionally, how to test private methods (and whether they should be tested).
* The adoption of an effective testing framework. In this case, I used [GoogleTest](https://github.com/google/googletest). 
* Lastly, the extension of a testing paradigm into other levels of testing as well as concepts such as Mocking.

While most software organizations I've worked with involve some sort of guidance in the form of a [Software Design Description](https://en.wikipedia.org/wiki/Software_design_description), of equal importance is the [Test Plan](https://en.wikipedia.org/wiki/Test_plan) which "documents the strategy that will be used to verify and ensure that a product or system meets its design specifications and other requirements." While test-driven devleopment typically refers to the unit test level, its principal can be applied to all levels of testing as a product matures.


# Building:
In order to build the executable, create a build directory (.e.g. build) where you will execute CMake from. The process below can be used to build the
qtGameOfLife executable.
* `git clone https://github.com/bruckart/qtGameOfLife`
* `cd qtGameOfLife`
* `mkdir build`
* `cd build`
* `cmake ../` (or cmake -DCMAKE_TESTING_ENABLED=1 ../)
* `make`


# Dependencies
This executable was written in C++ (17) and leverages GoogleTest for the 
unit tests. 


# Tests
The qtGameOfLife executable contains 6 unit tests that can
be built and executed via specifying the CMake flag `-DCMAKE_TESTING_ENABLED`. The test output should contain the following:

```
$ ./test/testGameOfLife
[==========] Running 6 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 6 tests from GameofLifeTestFixture
[ RUN      ] GameofLifeTestFixture.CellLifecycle
[       OK ] GameofLifeTestFixture.CellLifecycle (0 ms)
[ RUN      ] GameofLifeTestFixture.Cells
[       OK ] GameofLifeTestFixture.Cells (0 ms)
[ RUN      ] GameofLifeTestFixture.RuleOne
[       OK ] GameofLifeTestFixture.RuleOne (0 ms)
[ RUN      ] GameofLifeTestFixture.RuleTwo
[       OK ] GameofLifeTestFixture.RuleTwo (0 ms)
[ RUN      ] GameofLifeTestFixture.RuleThree
[       OK ] GameofLifeTestFixture.RuleThree (0 ms)
[ RUN      ] GameofLifeTestFixture.RuleFour
[       OK ] GameofLifeTestFixture.RuleFour (0 ms)
[----------] 6 tests from GameofLifeTestFixture (0 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 1 test suite ran. (1 ms total)
[  PASSED  ] 6 tests.
```

# Contributing
Please feel free to contribute to this project. 
For questions or comments, feel free to reach out to me on GitHub or my email at bruckart@gmail.com.

    1. Fork it (https://github.com/bruckart/qtGameOfLife.git)
    2. Create your feature branch (git checkout -b feature/fooBar)
    3. Commit your changes (git commit -am 'Add some fooBar')
    4. Push to the branch (git push origin feature/fooBar)
    5. Create a new Pull Request

