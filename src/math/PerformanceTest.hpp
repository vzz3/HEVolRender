namespace ppvr {
	namespace math {
		/**
		 * This class is not thread save => every thread need its own Random instance!
		 */
		class PerformanceTest {
		
		public:
			static void fromString();
			static void createPrime();
			
			static void modPow();
		
		// ----- constructors -----
		public:
			PerformanceTest();
			~PerformanceTest();
		};
	}
}
