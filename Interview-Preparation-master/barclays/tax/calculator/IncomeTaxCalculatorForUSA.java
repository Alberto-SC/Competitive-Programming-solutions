package com.interview.barclays.tax.calculator;

import com.interview.barclays.profile.IncomeProfile;

/*
 * Sample TaxSlab Used:
 * $0—$9,275	- 10%
 * $9,276—$37,650	- $927.50 plus 15% of the amount over $9,275
 * $37,651—$91,150	- $5,183.75 plus 25% of the amount over $37,650
 * $91,151—$190,150	- $18,558.75 plus 28% of the amount over $91,150
 * $190,151—$ 413,350	- $46,278.75 plus 33% of the amount over $190,150
 * $413,351—$415,050	- $119,934.75 plus 35% of the amount over $413,350
 * $415,051 or more	- $120,529.75 plus 39.6% of the amount over $415,050
 * 
 */

public class IncomeTaxCalculatorForUSA implements BaseIncomeTaxCalculator {
	
	private static final double TAX_RATE_1 = 0.1;
	
	private static final int TAX_LIMIT_1 = 9275;
	
	private static final double TAX_CONSTANT_1 = 927.5;
	
	private static final int TAX_LIMIT_2 = 37650;
	
	private static final double TAX_RATE_2 = .15;
	
	private static final double TAX_CONSTANT_2 = 5183.75;
	
	private static final int TAX_LIMIT_3 = 91150;
	
	private static final double TAX_RATE_3 = .25;
	
	private static final double TAX_CONSTANT_3 = 18558.75;
	
	private static final int TAX_LIMIT_4 = 190150;
	
	private static final double TAX_RATE_4 = .28;
	
	private static final double TAX_CONSTANT_4 = 46278.75;

	private static final int TAX_LIMIT_5 = 413350;
	
	private static final double TAX_RATE_5 = .33;
	
	private static final double TAX_CONSTANT_5 = 119934.75;

	private static final int TAX_LIMIT_6 = 415050;
	
	private static final double TAX_RATE_6 = .35;
	
	private static final double TAX_CONSTANT_6 = 120529.75;
	
	private static final double TAX_RATE_7 = .396;
	
	

	@Override
	public double calculateTax(IncomeProfile profile) {
		double tax = 0.0;
		double taxableIncome = profile.getTaxableIncome();
		if(taxableIncome > TAX_LIMIT_6){
			tax = (taxableIncome - TAX_LIMIT_6)*TAX_RATE_7
					+ TAX_CONSTANT_6;
		}else if(taxableIncome > TAX_LIMIT_5){
			tax = (taxableIncome - TAX_LIMIT_5)*TAX_RATE_6
					+ TAX_CONSTANT_5;
		}else if (taxableIncome > TAX_LIMIT_4){
			tax = (taxableIncome - TAX_LIMIT_4)*TAX_RATE_5
					+TAX_CONSTANT_4;
		}else if(taxableIncome > TAX_LIMIT_3){
			tax = (taxableIncome - TAX_LIMIT_3)*TAX_RATE_4
					+ TAX_CONSTANT_3;
		}else if(taxableIncome > TAX_LIMIT_2){
			tax = (taxableIncome - TAX_LIMIT_2)*TAX_RATE_3
					+ TAX_CONSTANT_2;
		}else if(taxableIncome > TAX_LIMIT_1){
			tax = (taxableIncome - TAX_LIMIT_1)*TAX_RATE_2
					+ TAX_CONSTANT_1;
		}else{
			tax = taxableIncome*TAX_RATE_1;
		}
		
		return tax;
	}

}
