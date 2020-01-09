/**
 * The main entry point.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2018-2019, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.System.hpp"

/**
 * The main function.
 *
 * The following tasks must be done before the function called:
 * 1. Stack has been set.
 * 2. CPU registers have been set.
 * 3. Run-time initialization has been completed.
 * 4. Global variables have been set.
 * 5. Global constructors have been called.
 *
 * @return error code or zero.
 */
int main()
{
    ::local::int32 error;
    // Execute the EOOS RT operating system
    try
    {
        ::local::system::System eoos;
        error = eoos.execute();
    }
	// Handle unexpected exceptions following MISRA-C++:2008 Rule 15–3–2 and AUTOSAR C++14 Rule A15-3-2
    catch (...)
    {
        error = ::local::ERROR_UNDEFINED;
    }
    return static_cast<int>(error);
}
