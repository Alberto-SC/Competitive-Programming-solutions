package com.interview.barclays.savings;

public enum SavingsGroupsForUSA {
	
	SECTION_SAMPLE_1 {
		@Override
		public double getMaxLimit() {
			return 30000;
		}
	},
	
	SECTION_SAMPLE_2 {
		@Override
		public double getMaxLimit() {
			return 50000;
		}
	};
	
	public abstract double getMaxLimit();

}
