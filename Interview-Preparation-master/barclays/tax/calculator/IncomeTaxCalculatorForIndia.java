package com.interview.barclays.tax.calculator;

import com.interview.barclays.profile.IncomeProfile;

/*
 * Sample TaxSlab Used: Income upto Rs 2,50,000 - NIL Income between Rs.
 * 2,50,001 - Rs. 500,000 - 10% of Income exceeding Rs. 2,50,000 Income between
 * Rs. 500,001 - Rs. 10,00,000 - 20% of Income exceeding Rs. 5,00,000 Income
 * above Rs. 10,00,000 - 30% of Income exceeding Rs. 10,00,000
 * 
 */

public class IncomeTaxCalculatorForIndia implements BaseIncomeTaxCalculator {

	private static final int NIL_TAX_LIMIT = 250000;

	private static final int TAX_LIMIT_1 = 500000;

	private static final double TAX_RATE_1 = 0.1;

	private static final double TAX_CONSTANT_2 = (TAX_LIMIT_1 - NIL_TAX_LIMIT) * TAX_RATE_1;

	private static final double TAX_RATE_2 = 0.2;

	private static final double TAX_RATE_3 = 0.3;

	private static final int TAX_LIMIT_2 = 1000000;

	private static final double TAX_CONSTANT_1 = (TAX_LIMIT_2 - TAX_LIMIT_1) * TAX_RATE_2;

	@Override
	public double calculateTax(IncomeProfile profile) {
		double tax = 0.0;
		double taxableIncome = profile.getTaxableIncome();
		if (taxableIncome > TAX_LIMIT_2) {
			tax = (taxableIncome - TAX_LIMIT_2) * TAX_RATE_3 + TAX_CONSTANT_1 + TAX_CONSTANT_2;
		} else if (taxableIncome > TAX_LIMIT_1) {
			tax = (taxableIncome - TAX_LIMIT_1) * TAX_RATE_2 + TAX_CONSTANT_2;
		} else if (taxableIncome > NIL_TAX_LIMIT) {
			tax = (taxableIncome - NIL_TAX_LIMIT) * TAX_RATE_1;
		}
		return tax;
	}

}
