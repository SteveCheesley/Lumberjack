# Testing

The lumberjack library is designed to have a comprehensive suite of tests aimed at validating functionality and performance (where appropriate).

## Unit Tests

The project employs unit test to validate the basic functionality of the library and contract its usage.

To execute all unit tests, simply run...

```bash
./test.sh
```

If you wish to run a single test, simply run the following

```bash
./test.sh -t <testsuite>.<testcase>
```
For example...
```bash
./test.sh -t DefaultLogFormatterTest.BasicSuccessTest
```

You can also run all tests in a specifc test suite by using a wildcard specifier...

```bash
./test.sh -t SourceMessageAppenderTest.*
```

If you want to execute procedural tests, don't forget to prefix with the data set name like this...

```bash
./test.sh -t MessageFormatCases/DefaultLogFormatterTest.*
```

### Debugging / Breakpointing Tests

This project supports the ability to add breakpoints to unit tests and debug them. This makes troubleshooting issues much more straightforward. This is achieved through a combination of 
existing build scripts and developer environment configuration.

#### Step 1: Configure `launch.json` (One Time Operation)
The first step is to configure the launch.json with profiles for executing specific tests:

```{json}
    "configurations": [
        {
            "name": "Debug All GoogleTests",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/lumberjack_tests",
            "args": [
                "--gtest_filter=*",
                "--gtest_break_on_failure",
                "--gtest_catch_exceptions=0"
            ],
            "cwd": "${workspaceFolder}",
            "MIMode": "gdb",
            "externalConsole": false
        },
        {
            "name": "Debug Single GoogleTest",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/lumberjack_tests",
            "args": [
                "--gtest_filter=DefaultLogFormatterTest.*"
            ],
            "cwd": "${workspaceFolder}",
            "MIMode": "gdb",
            "externalConsole": false
        }
    ]
```
Be sure to add these configurations. You only really need one, depending on your requirements. I have added both for convenience.

#### Step 2: Initialise build instructions and build
Once the proper configuration is ready, now we initialise and build. We do so by specifying the "debug" option on the build initialisation.

```bash
./build_init.sh -d -t
```
Then...

```bash
./build.sh
```

With the build executed successfully you are free to debug.

#### Step 3: Place breakpoint and run test
Finally, simply go to the run and debug sidebar menu and select the desired new debug profile and run. Be sure to add your desired breakpoint before you execute!