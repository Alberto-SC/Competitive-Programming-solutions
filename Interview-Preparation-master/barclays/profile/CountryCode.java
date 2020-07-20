package com.interview.barclays.profile;

import com.interview.barclays.savings.ExemptionsForIndia;
import com.interview.barclays.savings.ExemptionsForUSA;
import com.interview.barclays.savings.SavingScheme;
import com.interview.barclays.tax.calculator.BaseIncomeTaxCalculator;
import com.interview.barclays.tax.calculator.IncomeTaxCalculatorForIndia;
import com.interview.barclays.tax.calculator.IncomeTaxCalculatorForUSA;

public enum CountryCode {
	INDIA {
		@Override
		public BaseIncomeTaxCalculator getCalculator() {
			return new IncomeTaxCalculatorForIndia();
		}

		@Override
		public SavingScheme getSavingScheme() {
			return new ExemptionsForIndia();
		}
	},
	USA {
		@Override
		public BaseIncomeTaxCalculator getCalculator() {
			return new IncomeTaxCalculatorForUSA();
		}

		@Override
		public SavingScheme getSavingScheme() {
			return new ExemptionsForUSA();
		}
	};
    public abstract BaseIncomeTaxCalculator getCalculator();
    
    public abstract SavingScheme getSavingScheme();
    
}
