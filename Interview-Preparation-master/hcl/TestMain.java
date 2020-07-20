package com.interview.hcl;

import java.util.Date;

class TestMain
{
    public static void main(String[] args)
    {
        ImmutableClass im = ImmutableClass.createNewInstance(100,"test", new Date());
        System.out.println(im);
        tryModification(im.getImmutableField1(),im.getImmutableField2(),im.getMutableField());
        System.out.println(im);
    }
 
    private static void tryModification(Integer immutableField1, String immutableField2, Date mutableField)
    {
        immutableField1 = 10000;
        immutableField2 = "test changed";
        mutableField.setDate(10);
    }
}
 
/*
Output: (content is unchanged)

100 - test - Tue Oct 30 21:34:08 IST 2012
100 - test - Tue Oct 30 21:34:08 IST 2012
*/