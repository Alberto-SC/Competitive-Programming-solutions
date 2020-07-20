package com.interview.barclays.savings;

public enum SavingsGroupsForIndia {
	
	SECTION_80_C {
		@Override
		public double getMaxLimit() {
			return 150000;
		}
	},
	SECTION_80_D {
		@Override
		public double getMaxLimit() {
			return 100000;
		}
	};

	
    public abstract double getMaxLimit();

}
