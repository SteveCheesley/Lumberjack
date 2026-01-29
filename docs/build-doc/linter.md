# Linter

This project uses clang-tidy as a linter to ensure code quality. This project was written by someone learning C++ but who has a strong Java background. I also didn't think to use a linter from the get-go so there is technical debt in the project. To that end there are a large number of build failures and the CI build will allow the linter to fail at the moment. I will work to bring the violations down to 0. 

The current project rules are as follows:

1. **Clean-as-you-go** - Try to fix issues along the way
2. **Don't introduce new violations** - As you write more code, please, no new violations. Clean them up before submitting a code review