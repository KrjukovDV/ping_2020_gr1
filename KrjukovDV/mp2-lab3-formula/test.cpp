#include "pch.h"
#include "Formula.h"
TEST(Formula, can_create)
{
    ASSERT_NO_THROW(Formula f("  "));
}
TEST(Formula, can_accept_formula)
{
    ASSERT_NO_THROW(Formula f("6-(3*3)-3"));
}

TEST(Formula, check_brackets)
{
    Formula f("((53+ 3)-((3+2)");
    ASSERT_EQ(2, f.checkBrackets());
}

TEST(Formula, currect_analysis)
{
    Formula f("34+588");
    ASSERT_EQ(34, f.analysis()->pop()->getVal());
}


TEST(Formula, currect_result_with_two_values_and_operation_sum)
{
    Formula f("53+ 3");
    ASSERT_EQ(56, f.FormulaCalculator());
}

TEST(Formula, currect_result_with_two_values_and_operation_min)
{
    Formula f("23- 2");
    ASSERT_EQ(21, f.FormulaCalculator());
}

TEST(Formula, currect_result_with_two_values_and_operation_sub)
{
    Formula f("23* 3");
    ASSERT_EQ(69, f.FormulaCalculator());
}

TEST(Formula, currect_result_with_two_values_and_operation_div)
{
    Formula f("32/ 2");
    ASSERT_EQ(16, f.FormulaCalculator());
}

TEST(Formula, currect_result_with_more_currect_values_and_operations)
{
    Formula f("22 + 33 - 5");
    ASSERT_EQ(50, f.FormulaCalculator());
}

TEST(Formula, can_accept_example_with_brackets)
{
    Formula f("5 * (12 -8)");
    ASSERT_NO_THROW(f.FormulaCalculator());
}

TEST(Formula, currect_result_with_brackets)
{
    Formula f("5 * (12 -8)");
    ASSERT_EQ(20, f.FormulaCalculator());
}

TEST(Formula, cant_arithmetic_long_example)
{
    Formula f(" (228+757)*74+581618");
    ASSERT_EQ(654508, f.FormulaCalculator());
}
