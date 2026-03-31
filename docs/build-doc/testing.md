# Testing

The lumberjack library is designed to have a comprehensive suite of tests aimed at validating functionality and performance (where appropriate).

To run all tests, simply run...

```bash
./test.sh
```

## Integration Tests

The project has limited integration testing to validate usage of the library end-to-end.

To execute all integration tests, simply run...

```bash
./test.sh -t integration
```

## Unit Tests

The project employs unit test to validate the basic functionality of the library and contract its usage.

To execute all unit tests, simply run...

```bash
./test.sh -t unit
```

## Specific Test Execution

There may be times when you want to run one single test or all tests in a specific test suite. The test bash script gives us shortcuts to allow for execution of these cases too.

### Run a Single Test

If you wish to run a single test...

```bash
./test.sh -t <test-type> -f <testsuite>.<testcase>
```

A practical example of this could be the basic success test for the `DefaultLogFormatterTest`...

```bash
./test.sh -t unit -f DateMessageAppenderTest.testBasicSuccess
```

### Run a Test Suite

You can also run all tests in a specifc test suite by using a wildcard specifier...

```bash
./test.sh -t unit -f SourceMessageAppenderTest.*
```

### Run Procedural Tests

If you want to execute procedural tests, don't forget to prefix with the data set name like this...

```bash
./test.sh -t unit -f MessageFormatCases/DefaultLogFormatterTest.*
```

## VSCode

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
            "program": "${workspaceFolder}/build/lumberjack_unit_tests",
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
            "program": "${workspaceFolder}/build/lumberjack_unit_tests",
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

## Memory Leak Testing

This project used AddressSanitizer to search for memory leaks and other issues that might occur within the system. My eventual aim is to add this testing to the CI. Until I get all of the discovered issues fixed, this is a test that will be executed manually.

I carry out these tests against the end-to-end integration test that I have. Technically it could be run with any of the tests that are present in the system.

To run the AddressSanitizer testing, simply execute the following...

```bash
./build_init.sh -m -t -d
```

Once the build is prepared, execute it...

```bash
./build.sh
```

Finally, execute the test with pre-specified memory testing options...

```bash
./test.sh -m -t integration
```