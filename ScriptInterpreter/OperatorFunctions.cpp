#include "OperatorFunctions.h"
#include "String.h"

        unsigned int SCRIPT::OPERATOR::add(void* a, unsigned int a_type,
                         const void* val_1, const unsigned int val_1_type,
                         const void* val_2, const unsigned int val_2_type)
        {
            if(a_type == STR)
            {
                if(val_1_type != STR)
                {
                    return ERROR_OPERATION_NOT_DEFINED;
                }
                switch(val_2_type)
                {
                case STR:
                    *(String*)a  = *(String*)val_1 + *(String*)val_2;
                    return NO_ERROR;
                    break;
                case INT:
                    *(String*)a  = *(String*)val_1 + *(int*)val_2;
                    return NO_ERROR;
                    break;
                case BOOL:
                    *(String*)a  = *(String*)val_1 + *(bool*)val_2;
                    return NO_ERROR;
                    break;
                case FLOAT:
                    *(String*)a  = *(String*)val_1 + *(float*)val_2;
                    return NO_ERROR;
                }
            }
            else
            {
                if(val_1_type == STR || val_2_type == STR)
                    return ERROR_OPERATION_NOT_DEFINED;
            }
            if(a_type == INT)
            {
                if(val_1_type == INT)
                {
                    if(val_2_type == INT)
                    {
                        *(int*)a = *(int*)val_1 + *(int*)val_2;
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(int*)a = *(int*)val_1 + *(float*)val_2;
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == FLOAT)
                {
                    if(val_2_type == INT)
                    {
                        *(int*)a = *(float*)val_1 + *(int*)val_2;
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(int*)a = *(float*)val_1 + *(float*)val_2;
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == BOOL)
                {
                    if(val_2_type == INT)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == FLOAT)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
            }
            else if(a_type == FLOAT)
            {
                if(val_1_type == INT)
                {
                    if(val_2_type == INT)
                    {
                        *(float*)a = *(int*)val_1 + *(int*)val_2;
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(float*)a = *(int*)val_1 + *(float*)val_2;
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == FLOAT)
                {
                    if(val_2_type == INT)
                    {
                        *(float*)a = *(float*)val_1 + *(int*)val_2;
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(float*)a = *(float*)val_1 + *(float*)val_2;
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == BOOL)
                {
                    if(val_2_type == INT)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == FLOAT)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
            }
            else if(a_type == BOOL)
            {
                if(val_1_type == INT)
                {
                    if(val_2_type == INT)
                    {
                        *(bool*)a = *(int*)val_1 + *(int*)val_2;
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(bool*)a = *(int*)val_1 + *(float*)val_2;
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == FLOAT)
                {
                    if(val_2_type == INT)
                    {
                        *(bool*)a = *(float*)val_1 + *(int*)val_2;
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(bool*)a = *(float*)val_1 + *(float*)val_2;
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == BOOL)
                {
                    if(val_2_type == INT)
                    {
                         return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == FLOAT)
                    {
                         return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == BOOL)
                    {
                         return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
            }
            return NO_ERROR;
        }
        unsigned int SCRIPT::OPERATOR::subtract(void* a, unsigned int a_type,
                              const void* val_1, const unsigned int val_1_type,
                              const void* val_2, const unsigned int val_2_type)
        {
            if(a_type == STR || val_1_type == STR || val_2_type == STR)
                return ERROR_OPERATION_NOT_DEFINED;

            if(a_type == INT)
            {
                if(val_1_type == INT)
                {
                    if(val_2_type == INT)
                    {
                        *(int*)a = *(int*)val_1 - *(int*)val_2;
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(int*)a = *(int*)val_1 - *(float*)val_2;
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == FLOAT)
                {
                    if(val_2_type == INT)
                    {
                        *(int*)a = *(float*)val_1 + *(int*)val_2;
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(int*)a = *(float*)val_1 + *(float*)val_2;
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == BOOL)
                {
                    if(val_2_type == INT)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == FLOAT)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
            }
            else if(a_type == FLOAT)
            {
                if(val_1_type == INT)
                {
                    if(val_2_type == INT)
                    {
                        *(float*)a = *(int*)val_1 - *(int*)val_2;
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(float*)a = *(int*)val_1 - *(float*)val_2;
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == FLOAT)
                {
                    if(val_2_type == INT)
                    {
                        *(float*)a = *(float*)val_1 - *(int*)val_2;
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(float*)a = *(float*)val_1 - *(float*)val_2;
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == BOOL)
                {
                    if(val_2_type == INT)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == FLOAT)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
            }
            else if(a_type == BOOL)
            {
                if(val_1_type == INT)
                {
                    if(val_2_type == INT)
                    {
                        *(bool*)a = *(int*)val_1 - *(int*)val_2;
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(bool*)a = *(int*)val_1 - *(float*)val_2;
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == FLOAT)
                {
                    if(val_2_type == INT)
                    {
                        *(bool*)a = *(float*)val_1 - *(int*)val_2;
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(bool*)a = *(float*)val_1 - *(float*)val_2;
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == BOOL)
                {
                    if(val_2_type == INT)
                    {
                         return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == FLOAT)
                    {
                         return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == BOOL)
                    {
                         return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
            }
            return NO_ERROR;
        }
        unsigned int SCRIPT::OPERATOR::multiply(void* a, unsigned int a_type,
                              const void* val_1, const unsigned int val_1_type,
                              void* val_2, unsigned int val_2_type)
        {
            if(a_type == STR || val_1_type == STR || val_2_type == STR)
                return ERROR_OPERATION_NOT_DEFINED;

            if(a_type == INT)
            {
                if(val_1_type == INT)
                {
                    if(val_2_type == INT)
                    {
                        *(int*)a = *(int*)val_1 * (*(int*)val_2);
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(int*)a = *(int*)val_1 * (*(float*)val_2);
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == FLOAT)
                {
                    if(val_2_type == INT)
                    {
                        *(int*)a = *(float*)val_1 * (*(int*)val_2);
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(int*)a = *(float*)val_1 * (*(float*)val_2);
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == BOOL)
                {
                    if(val_2_type == INT)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == FLOAT)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
            }
            else if(a_type == FLOAT)
            {
                if(val_1_type == INT)
                {
                    if(val_2_type == INT)
                    {
                        *(float*)a = *(int*)val_1 * (*(int*)val_2);
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(float*)a = *(int*)val_1 * (*(float*)val_2);
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == FLOAT)
                {
                    if(val_2_type == INT)
                    {
                        *(float*)a = *(float*)val_1 * (*(int*)val_2);
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(float*)a = *(float*)val_1 * (*(float*)val_2);
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == BOOL)
                {
                    if(val_2_type == INT)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == FLOAT)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
            }
            else if(a_type == BOOL)
            {
                if(val_1_type == INT)
                {
                    if(val_2_type == INT)
                    {
                        *(bool*)a = *(int*)val_1 * (*(int*)val_2);
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(bool*)a = *(int*)val_1 * (*(float*)val_2);
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == FLOAT)
                {
                    if(val_2_type == INT)
                    {
                        *(bool*)a = *(float*)val_1 * (*(int*)val_2);
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(bool*)a = *(float*)val_1 * (*(float*)val_2);
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == BOOL)
                {
                    if(val_2_type == INT)
                    {
                         return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == FLOAT)
                    {
                         return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == BOOL)
                    {
                         return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
            }
            return NO_ERROR;
        }
        unsigned int SCRIPT::OPERATOR::divide(void* a, unsigned int a_type,
                            void* val_1, unsigned int val_1_type,
                            void* val_2, unsigned int val_2_type)
        {
            if(a_type == STR || val_1_type == STR || val_2_type == STR)
                return ERROR_OPERATION_NOT_DEFINED;

            if(a_type == INT)
            {
                if(val_1_type == INT)
                {
                    if(val_2_type == INT)
                    {
                        *(int*)a = *(int*)val_1 / (*(int*)val_2);
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(int*)a = *(int*)val_1 / (*(float*)val_2);
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == FLOAT)
                {
                    if(val_2_type == INT)
                    {
                        *(int*)a = *(float*)val_1 / (*(int*)val_2);
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(int*)a = *(float*)val_1 / (*(float*)val_2);
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == BOOL)
                {
                    if(val_2_type == INT)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == FLOAT)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
            }
            else if(a_type == FLOAT)
            {
                if(val_1_type == INT)
                {
                    if(val_2_type == INT)
                    {
                        *(float*)a = *(int*)val_1 / (*(int*)val_2);
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(float*)a = *(int*)val_1 / (*(float*)val_2);
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == FLOAT)
                {
                    if(val_2_type == INT)
                    {
                        *(float*)a = *(float*)val_1 / (*(int*)val_2);
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(float*)a = *(float*)val_1 / (*(float*)val_2);
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == BOOL)
                {
                    if(val_2_type == INT)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == FLOAT)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
            }
            else if(a_type == BOOL)
            {
                if(val_1_type == INT)
                {
                    if(val_2_type == INT)
                    {
                        *(bool*)a = *(int*)val_1 / (*(int*)val_2);
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(bool*)a = *(int*)val_1 / (*(float*)val_2);
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == FLOAT)
                {
                    if(val_2_type == INT)
                    {
                        *(bool*)a = *(float*)val_1 / (*(int*)val_2);
                    }
                    else if(val_2_type == FLOAT)
                    {
                        *(bool*)a = *(float*)val_1 / (*(float*)val_2);
                    }
                    else if(val_2_type == BOOL)
                    {
                        return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
                else if(val_1_type == BOOL)
                {
                    if(val_2_type == INT)
                    {
                         return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == FLOAT)
                    {
                         return ERROR_OPERATION_NOT_DEFINED;
                    }
                    else if(val_2_type == BOOL)
                    {
                         return ERROR_OPERATION_NOT_DEFINED;
                    }
                }
            }
            return NO_ERROR;
        }
        unsigned int SCRIPT::OPERATOR::assignVar(void* a, unsigned int a_type,
                               void* val, unsigned int val_type)
        {
            if(a_type == STR)
            {
                if(val_type != STR)
                {
                    return ERROR_OPERATION_NOT_DEFINED;
                }
                else
                {
                    *(String*)a = *(String*)val;
                }
            }

            if(a_type == INT)
            {
                if(val_type == INT)
                {
                    *(int*)a = *(int*)val;
                }
                else if(val_type == FLOAT)
                {
                    *(int*)a = *(float*)val;
                }
                else if(val_type == BOOL)
                {
                    *(int*)a = *(bool*)val;
                }
            }
            else if(a_type == FLOAT)
            {
                if(val_type == INT)
                {
                    *(float*)a = *(int*)val;
                }
                else if(val_type == FLOAT)
                {
                    *(float*)a = *(float*)val;
                }
                else if(val_type == BOOL)
                {
                    *(float*)a = *(bool*)val;
                }
            }
            else if(a_type == BOOL)
            {
                if(val_type == INT)
                {
                    *(bool*)a = *(int*)val;
                }
                else if(val_type == FLOAT)
                {
                    *(bool*)a = *(float*)val;
                }
                else if(val_type == BOOL)
                {
                    *(bool*)a = *(bool*)val;
                }
            }

            return NO_ERROR;
        }
        unsigned int SCRIPT::LOGIC::lessThan(bool& result, void* val_1, unsigned int val_1_type,
                              void* val_2, unsigned int val_2_type)
        {
            if(val_1_type == STR || val_2_type == STR)
                return ERROR_OPERATION_NOT_DEFINED;
            if(val_1_type == INT)
            {
                if(val_2_type == INT)
                {
                    result = false;
                    if((*(int*)val_1) < *(int*)val_2)
                    {
                        result = true;
                    }
                }
                else if(val_2_type == FLOAT)
                {
                    result = false;
                    if((*(int*)val_1) < *(float*)val_2)
                    {
                        result = true;
                    }
                }
                else if(val_2_type == BOOL)
                {
                    result = false;
                    if((*(int*)val_1) < *(bool*)val_2)
                    {
                        result = true;
                    }
                }
            }
            else if(val_1_type == FLOAT)
            {
                if(val_2_type == INT)
                {
                    result = false;
                    if((*(float*)val_1) < *(int*)val_2)
                    {
                        result = true;
                    }
                }
                else if(val_2_type == FLOAT)
                {
                    result = false;
                    if((*(float*)val_1) < *(float*)val_2)
                    {
                        result = true;
                    }
                }
                else if(val_2_type == BOOL)
                {
                    result = false;
                    if((*(float*)val_1) < *(bool*)val_2)
                    {
                        result = true;
                    }
                }
            }
            else if(val_1_type == BOOL)
            {
                if(val_2_type == INT)
                {
                    result = false;
                    if((*(bool*)val_1) < *(int*)val_2)
                    {
                        result = true;
                    }
                }
                else if(val_2_type == FLOAT)
                {
                    result = false;
                    if((*(bool*)val_1) < *(float*)val_2)
                    {
                        result = true;
                    }
                }
                else if(val_2_type == BOOL)
                {
                    result = false;
                    if((*(bool*)val_1) < *(bool*)val_2)
                    {
                        result = true;
                    }
                }
            }

            return NO_ERROR;
        }
        unsigned int SCRIPT::LOGIC::moreThan(bool& result, void* val_1, unsigned int val_1_type,
                              void* val_2, unsigned int val_2_type)
        {
            if(val_1_type == STR || val_2_type == STR)
                return ERROR_OPERATION_NOT_DEFINED;

            if(val_1_type == INT)
            {
                if(val_2_type == INT)
                {
                    result = false;
                    if((*(int*)val_1) > *(int*)val_2)
                    {
                        result = true;
                    }
                }
                else if(val_2_type == FLOAT)
                {
                    result = false;
                    if((*(int*)val_1) > *(float*)val_2)
                    {
                        result = true;
                    }
                }
                else if(val_2_type == BOOL)
                {
                    result = false;
                    if((*(int*)val_1) > *(bool*)val_2)
                    {
                        result = true;
                    }
                }
            }
            else if(val_1_type == FLOAT)
            {
                if(val_2_type == INT)
                {
                    result = false;
                    if((*(float*)val_1) > *(int*)val_2)
                    {
                        result = true;
                    }
                }
                else if(val_2_type == FLOAT)
                {
                    result = false;
                    if((*(float*)val_1) > *(float*)val_2)
                    {
                        result = true;
                    }
                }
                else if(val_2_type == BOOL)
                {
                    result = false;
                    if((*(float*)val_1) == *(bool*)val_2)
                    {
                        result = true;
                    }
                }
            }
            else if(val_1_type == BOOL)
            {
                if(val_2_type == INT)
                {
                    result = false;
                    if((*(bool*)val_1) > *(int*)val_2)
                    {
                        result = true;
                    }
                }
                else if(val_2_type == FLOAT)
                {
                    result = false;
                    if((*(bool*)val_1) > *(float*)val_2)
                    {
                        result = true;
                    }
                }
                else if(val_2_type == BOOL)
                {
                    result = false;
                    if((*(bool*)val_1) > *(bool*)val_2)
                    {
                        result = true;
                    }
                }
            }

            return NO_ERROR;
        }
        unsigned int SCRIPT::LOGIC::equals(bool& result, void* val_1, unsigned int val_1_type,
                            void* val_2, unsigned int val_2_type)
        {
            if(val_1_type == STR)
            {
                if(val_2_type != STR)
                {

                }
                else
                {
                    result = false;
                    if(*(String*)val_1 == *(String*)val_2)
                    {
                        result = true;
                    }
                }
            }
            if(val_1_type == INT)
            {
                if(val_2_type == INT)
                {
                    result = false;
                    if((*(int*)val_1) == *(int*)val_2)
                    {
                        result = true;
                    }
                }
                else if(val_2_type == FLOAT)
                {
                    result = false;
                    if((*(int*)val_1) == *(float*)val_2)
                    {
                        result = true;
                    }
                }
                else if(val_2_type == BOOL)
                {
                    result = false;
                    if((*(int*)val_1) == *(bool*)val_2)
                    {
                        result = true;
                    }
                }
            }
            else if(val_1_type == FLOAT)
            {
                if(val_2_type == INT)
                {
                    result = false;
                    if((*(float*)val_1) == *(int*)val_2)
                    {
                        result = true;
                    }
                }
                else if(val_2_type == FLOAT)
                {
                    result = false;
                    if((*(float*)val_1) == *(float*)val_2)
                    {
                        result = true;
                    }
                }
                else if(val_2_type == BOOL)
                {
                    result = false;
                    if((*(float*)val_1) == *(bool*)val_2)
                    {
                        result = true;
                    }
                }
            }
            else if(val_1_type == BOOL)
            {
                if(val_2_type == INT)
                {
                    result = false;
                    if((*(bool*)val_1) == *(int*)val_2)
                    {
                        result = true;
                    }
                }
                else if(val_2_type == FLOAT)
                {
                    result = false;
                    if((*(bool*)val_1) == *(float*)val_2)
                    {
                        result = true;
                    }
                }
                else if(val_2_type == BOOL)
                {
                    result = false;
                    if((*(bool*)val_1) == *(bool*)val_2)
                    {
                        result = true;
                    }
                }
            }

            return NO_ERROR;
        }
