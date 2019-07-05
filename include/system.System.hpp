/**
 * The operating system class.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2019, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_SYSTEM_HPP_
#define SYSTEM_SYSTEM_HPP_

#include "system.Object.hpp"
#include "api.System.hpp"
#include "Configuration.hpp"
#include "Error.hpp"

namespace local
{
    namespace system
    {
        class System : public system::Object, public api::System
        {
            typedef system::System Self;
            typedef system::Object Parent;

        public:

            /**
             * Constructor.
             */
            System();

            /**
             * Destructor.
             */
            virtual ~System();

            /**
             * Tests if this object has been constructed.
             *
             * @return true if object has been constructed successfully.
             */
            virtual bool isConstructed() const;

            /**
             * Returns running time of the operating system in nanoseconds.
             *
             * @return time in nanoseconds.
             */
            virtual int64 getTime() const;

            /**
             * Returns the operating system heap memory.
             *
             * @return the heap memory.
             */
            virtual api::Heap& getHeap() const;

            /**
             * Returns the system runtime environment.
             *
             * @return the system runtime environment.
             */
            virtual api::Runtime& getRuntime() const;

            /**
             * Returns a global interrupt controller.
             *
             * @return a global interrupt controller.
             */
            virtual api::Toggle& getGlobalInterrupt() const;

            /**
             * Returns the kernel scheduler.
             *
             * @return the kernel scheduler.
             */
            virtual api::Scheduler& getScheduler() const;

            /**
             * Creates a new mutex resource.
             *
             * @return a new mutex resource, or NULL if an error has been occurred.
             */
            virtual api::Mutex* createMutex();

            /**
             * Creates a new semaphore resource.
             *
             * @param permits - the initial number of permits available.
             * @param isFair  - true if this semaphore will guarantee FIFO granting of permits under contention.
             * @return a new semaphore resource, or NULL if an error has been occurred.
             */
            virtual api::Semaphore* createSemaphore(int32 permits, bool isFair);

            /**
             * Creates a new interrupt resource.
             *
             * @param handler - user class which implements an interrupt handler interface.
             * @param source  - available interrupt source number.
             * @return a new interrupt resource, or NULL if an error has been occurred.
             */
            virtual api::Interrupt* createInterrupt(api::Task& handler, int32 source);

            /**
             * Terminates the operating system execution.
             */
            virtual void terminate() const;

            /**
             * Executes the operating system.
             *
             * @return zero, or error code if the execution has been terminated.
             */
            int32 execute();

            /**
             * Returns the operating system syscall interface.
             *
             * @return the operating system syscall interface.
             */
            static api::System& call();

        private:

            /**
             * Constructs this object.
             *
             * @return true if object has been constructed successfully.
             */
            bool construct();

            /**
             * Terminates the operating system execution.
             *
             * @param error a termination status code.
             */
            static void terminate(Error error);

            /**
             * The operating system interface.
             */
            static api::System* system_;

            /**
             * Configuration of the operating system .
             *
             * NOTE: The variable must be the first, as it must be initialized first.
             */
            const Configuration config_;

        };
    }
}
#endif // SYSTEM_SYSTEM_HPP_
