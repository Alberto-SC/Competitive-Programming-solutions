package com.interview.optymyze;
import java.util.Scanner;
import java.util.Stack;
public class BalanacedParentheses {

    static Stack<Character> charStack = new Stack<Character>();

    public static boolean validateParentheses(String input) {
        if (input != null && !input.isEmpty()) {
            for (int i = 0; i < input.length(); i++) {
                char c = input.charAt(i);
                if (c == '{' || c == '[' || c == '(') {
                    charStack.push(c);
                } else if (c == '}' || c == ']' || c == ')') {
                    if (charStack.isEmpty())
                        return false;
                    switch (c) {
                        case '}':
                            if (charStack.pop() != '{')
                                return false;
                            break;
                        case ']':
                            if (charStack.pop() != '[')
                                return false;
                            break;
                        case ')':
                            if (charStack.pop() != '(')
                                return false;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        if (charStack.isEmpty())
            return true;
        return false;

    }

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        System.out.println("Enter the input : ");
        System.out.println(validateParentheses(in.next()));
    }

    /**
     * Input: {}()[]
     * Output: True
     *
     * Input: ({[]})
     * Output: True
     *
     * Input: {})
     * Output: false
     */
}