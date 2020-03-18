#include <iostream>
#include <windows.h>
#include <cmath>

using namespace std;
class BigNumber;
char* update_arr(char* im, unsigned int& oldSize);
int findMin(BigNumber* arr, int numberOfArrayElements);
int findMax(BigNumber* arr, int numberOfArrayElements);
bool areCharArraysEqual(char* first_arr, char* second_arr, int numberOfElements);

struct stack_output_num
{
    char num = '\0';
    stack_output_num* under = nullptr;
};

void push2Stack(char addNum, stack_output_num*& top)
{
    stack_output_num* newEl = new stack_output_num;
    newEl->num = addNum;
    newEl->under = top;
    top = newEl;
}

char popFromStack(stack_output_num*& top)
{
    if (top == nullptr)
        return 0;

    stack_output_num* temp = top;
    char num = top->num;
    top = top->under;
    delete temp;

    return num;
}

void printStack(stack_output_num* top)
{
    while (top != nullptr)
    {
        top = top->under;
    }
}

char* update_arr(char* ptr, unsigned int& oldSize)
{
    int temp = oldSize;
    oldSize += 10;

    char* newT = new char[oldSize];

    for (int i = 0; i < temp; i++)
    {
        newT[i] = ptr[i];
    }
    delete[] ptr;

    return newT;
}

class BigNumber
{
    char* m_ptr_char;
    int* m_ptr_int = { 0 };
    unsigned int m_arrLength = 0;
    unsigned int m_numberOfEl = 0;

public:

    BigNumber()
    {
        m_ptr_char = new char[1];
    }

    BigNumber operator- (BigNumber& secondNum);
    BigNumber operator+ (BigNumber& secondNum);

    bool set_char_arr();
    bool set_char_arr(BigNumber number2);
    char* get_char_ptr();

    void printCharArray();
    void printIntArray();

    void rewriteCharArrayToInt();
    void add_minus_to_array();
    void del_minus_from_array();

    BigNumber add_numbers_bothPlusOrMinus(BigNumber& secondNum);
    BigNumber sub_numbers_bothPlusOrMinus(BigNumber& secondNum);

    bool isGreaterThan(BigNumber& secondNum);
    bool isSmallerThan(BigNumber& secondNum);
    bool isMinus();

};

int main()
{
    int howManyNum, i = 0;
    bool noQuit = true;
    BigNumber chosenOption, * outputNumber;

    cout << "How many numbers you want to operate on?" << endl;
    cin >> howManyNum;

    BigNumber* arr = new BigNumber[howManyNum];

    cin.get();

    cout << "Now set numbers" << endl << endl;

    while (howManyNum > 0 && noQuit == true)
    {
        cout << endl << "Inject number: " << i + 1 << endl << endl;

        noQuit = arr[i].set_char_arr();
        i++;
        howManyNum--;
    }
    noQuit = true;
    howManyNum = i;

    system("cls");

    cout << "Array of given numbers:\n\n";
    for (int i = 0; i < howManyNum; i++)
    {
        cout << i << ". ";
        arr[i].printCharArray();
        cout << endl;
    }
    int index;
    cout << endl << "Commands:\n\n q to quit\n clear - to refresh arr\n \n MIN - find smallest number \n MAX - find biggest number \n \n To ADD and SUB numbers from index0,index1 and save them in index0 \n \n 0 = 0 + 1   - written this way " << endl;
    while (noQuit == true)
    {
        chosenOption.set_char_arr();

        if (areCharArraysEqual(chosenOption.get_char_ptr(), "MAX", 3))
        {
            index = findMax(arr, howManyNum);
            cout << "MAX number is: " << index << ". " << endl;
            arr[index].printCharArray();
        }
        else if (areCharArraysEqual(chosenOption.get_char_ptr(), "MIN", 3))
        {
            index = findMin(arr, howManyNum);
            cout << "MIN number is: " << index << ". " << endl;
            arr[index].printCharArray();
        }
        else if (areCharArraysEqual(chosenOption.get_char_ptr(), "clear", 4))
        {
            system("cls");
            cout << "Array of given numbers:\n\n";
            for (int i = 0; i < howManyNum; i++)
            {
                cout << i << ". ";
                arr[i].printCharArray();
                cout << endl;
            }
            cout << endl << "Commands:\n\n q to quit\n clear - to refresh arr\n \n MIN - find smallest number \n MAX - find biggest number \n \n To ADD and SUB numbers from index0,index1 and save them in index0 \n \n 0 = 0 + 1   - written this way " << endl;
        }

        else if (isdigit(int(chosenOption.get_char_ptr()[0])))
        {
            stack_output_num* numbersFromExpression = nullptr;
            int temp_int = 0, output_index, firstNumIndex, secondNumIndex, thirdNumIndex;
            char temp_char = 'x', sign;
            int i = 0, j = 0;

            while (chosenOption.get_char_ptr()[i] != ' ')
            {
                temp_char = chosenOption.get_char_ptr()[i];
                push2Stack(temp_char, numbersFromExpression);
                i++;
            }
            output_index = i;
            i = 0;
            while (numbersFromExpression != nullptr)
            {
                temp_char = popFromStack(numbersFromExpression);
                temp_int += (temp_char - 48) * pow(10, i);
                i++;
            }
            i += 3;
            firstNumIndex = temp_int;
            temp_int = 0;
            while (chosenOption.get_char_ptr()[i] != ' ')
            {
                temp_char = chosenOption.get_char_ptr()[i];
                push2Stack(temp_char, numbersFromExpression);

                i++;
            }
            output_index = i;
            i = 0;
            while (numbersFromExpression != nullptr)
            {
                temp_char = popFromStack(numbersFromExpression);
                temp_int += (temp_char - 48) * pow(10, i);
                i++;
            }

            i = output_index;
            i++;
            sign = chosenOption.get_char_ptr()[i];
            i = i + 2;

            secondNumIndex = temp_int;
            temp_int = 0;

            while (isdigit(int(chosenOption.get_char_ptr()[i])))
            {
                temp_char = chosenOption.get_char_ptr()[i];
                push2Stack(temp_char, numbersFromExpression);

                i++;
            }

            i = 0;
            while (numbersFromExpression != nullptr)
            {
                temp_char = popFromStack(numbersFromExpression);
                temp_int += (temp_char - 48) * pow(10, i);
                i++;
            }

            thirdNumIndex = temp_int;

            if (sign == '+')
            {
                arr[firstNumIndex].set_char_arr(arr[secondNumIndex] + arr[thirdNumIndex]);
                cout << "Output number is: ";
                arr[firstNumIndex].printCharArray();

            }
            else if (sign = '-')
            {
                cout << "Output number is: ";
                arr[firstNumIndex].set_char_arr(arr[secondNumIndex] - arr[thirdNumIndex]);
                arr[firstNumIndex].printCharArray();
            }
            else
            {
                return 0;
            }
        }

        else
        {
            cout << "Wrong command. Try again!" << endl;
        }
    }
}

BigNumber BigNumber::operator+ (BigNumber& secondNum)
{
    BigNumber outputNumber, * plusNumber, * minusNumber, * biggerNum, * smallerNum;
    bool wasSwapped = false;

    if (!this->isMinus() && !secondNum.isMinus())
    {
        outputNumber = this->add_numbers_bothPlusOrMinus(secondNum);
    }

    else if (this->isMinus() && secondNum.isMinus())
    {
        this->del_minus_from_array();

        secondNum.del_minus_from_array();
        outputNumber = this->add_numbers_bothPlusOrMinus(secondNum);
        outputNumber.add_minus_to_array();
    }

    else
    {
        if (this->isMinus())
        {
            plusNumber = &secondNum;
            minusNumber = this;
        }

        else
        {
            plusNumber = this;
            minusNumber = &secondNum;
        }

        minusNumber->del_minus_from_array();

        if (this->isGreaterThan(secondNum))
        {
            biggerNum = this;
            smallerNum = &secondNum;
        }

        else
        {
            smallerNum = this;
            biggerNum = &secondNum;
            wasSwapped = true;
        }

        outputNumber = biggerNum->sub_numbers_bothPlusOrMinus(*smallerNum);

        if (biggerNum == minusNumber)
        {
            outputNumber.add_minus_to_array();
        }
    }
    return outputNumber;
}

BigNumber BigNumber::operator- (BigNumber& secondNum)
{
    BigNumber* minuend = this, * subtrahend = &secondNum;
    bool wasSwapped = false;
    BigNumber outputNumber, * biggerNum, * smallerNum, * minusNumber, * plusNumber;
    if (!this->isMinus() && !secondNum.isMinus())
    {
        if (this->isGreaterThan(secondNum))
        {
            biggerNum = this;
            smallerNum = &secondNum;
        }
        else
        {
            smallerNum = this;
            biggerNum = &secondNum;
            wasSwapped = true;
        }

        outputNumber = biggerNum->sub_numbers_bothPlusOrMinus(*smallerNum);

        if (wasSwapped)
        {
            outputNumber.add_minus_to_array();
        }
    }

    else if (this->isMinus() && secondNum.isMinus())
    {
        this->del_minus_from_array();
        secondNum.del_minus_from_array();

        if (secondNum.isGreaterThan(*this))
        {
            biggerNum = &secondNum;
            smallerNum = this;
            outputNumber = biggerNum->sub_numbers_bothPlusOrMinus(*smallerNum);
        }
        else
        {
            smallerNum = &secondNum;
            biggerNum = this;
            outputNumber = biggerNum->sub_numbers_bothPlusOrMinus(*smallerNum);
            outputNumber.add_minus_to_array();
        }
    }

    else
    {
        if (this->isMinus())
        {
            plusNumber = &secondNum;
            minusNumber = this;
        }
        else
        {
            plusNumber = this;
            minusNumber = &secondNum;
        }

        minusNumber->del_minus_from_array();
        outputNumber = plusNumber->add_numbers_bothPlusOrMinus(*minusNumber);

        if (minusNumber == this)
        {
            outputNumber.add_minus_to_array();
        }
    }
    return outputNumber;
}

bool BigNumber::set_char_arr()
{
    char ch;
    unsigned int noOfElements = 0, index = 0;

    while (ch != '\n')
    {
        cin.get(ch);

        if (ch == 'q')
            return 0;

        noOfElements++;
        if (m_arrLength <= noOfElements)
        {
            m_ptr_char = update_arr(m_ptr_char, m_arrLength);
        }

        m_ptr_char[index] = ch;
        index++;
    }

    m_ptr_char[noOfElements] = '\0';
    m_ptr_int = new int[noOfElements] {};
    m_numberOfEl = noOfElements - 1;
}

bool BigNumber::set_char_arr(BigNumber number2)
{
    char ch;
    unsigned int noOfElements = 0, index = 0;

    for (int i = 0; i < number2.m_numberOfEl; i++)
    {

        if (m_arrLength <= number2.m_arrLength)
        {
            m_ptr_char = update_arr(m_ptr_char, m_arrLength);
        }

        m_ptr_char[i] = number2.m_ptr_char[i];
        noOfElements++;
    }

    m_ptr_char[noOfElements] = '\0';
    m_ptr_int = new int[noOfElements] {};
    m_numberOfEl = noOfElements - 1;
}

char* BigNumber::get_char_ptr()
{
    return m_ptr_char;
}

void BigNumber::printCharArray()
{
    cout << m_ptr_char << endl;
}

void BigNumber::printIntArray()
{
    for (int i = 0; i < m_numberOfEl; i++)
    {
        cout << m_ptr_int[i];
    }
    cout << endl;
}

void BigNumber::rewriteCharArrayToInt()
{
    for (int i = 0; i < m_numberOfEl; i++)
    {
        m_ptr_int[i] = (int)m_ptr_char[i] - 48;
    }
}

void BigNumber::add_minus_to_array()
{
    char* temp_char_arr = new char[this->m_numberOfEl + 3];
    int index0 = 0, index1 = 1;

    if (m_ptr_char[0] != '-')
    {
        if (m_arrLength <= this->m_numberOfEl)
        {
            m_ptr_char = update_arr(m_ptr_char, m_arrLength);
        }

        while (m_ptr_char[index0] != '\0')
        {
            temp_char_arr[index0] = m_ptr_char[index0];
            index0++;
        }

        m_ptr_char[0] = '-';
        index1 = index0;

        while (index0 > 0)
        {
            index0--;
            m_ptr_char[index0 + 1] = temp_char_arr[index0];
        }

        m_ptr_char[index1 + 1] = '\0';
        m_numberOfEl++;
    }
    delete[] temp_char_arr;
}

void BigNumber::del_minus_from_array()
{
    if (m_ptr_char[0] == '-')
    {
        int index0 = 0, index1 = 1;

        while (m_ptr_char[index1] != '\0')
        {
            m_ptr_char[index0] = m_ptr_char[index1];
            index0++;
            index1++;
        }
        m_ptr_char[index0] = '\0';
        m_numberOfEl--;
    }
}

BigNumber BigNumber::add_numbers_bothPlusOrMinus(BigNumber& secondNum)
{
    BigNumber* biggerNum, * smallerNum, outputNum;
    int index2 = 0, index3 = 0, sum = 0, sumTempOutput = 0;

    stack_output_num* outputNumberStack = nullptr;
    this->rewriteCharArrayToInt();
    secondNum.rewriteCharArrayToInt();
    if (this->m_numberOfEl >= secondNum.m_numberOfEl)
    {
        biggerNum = this;
        smallerNum = &secondNum;
    }

    else
    {
        biggerNum = &secondNum;
        smallerNum = this;
    }

    index2 = biggerNum->m_numberOfEl - 1;
    index3 = smallerNum->m_numberOfEl - 1;

    char temp;
    int index1 = biggerNum->m_numberOfEl;

    if (!this->isMinus() && !secondNum.isMinus())
    {
        outputNum.m_numberOfEl = biggerNum->m_numberOfEl + 1;
        outputNum.m_ptr_int = new int[biggerNum->m_numberOfEl + 1];
        outputNum.m_arrLength = biggerNum->m_arrLength + 1;
        while (index1 >= 0)
        {
            if (index3 >= 0)
            {
                sum += (biggerNum->m_ptr_int[index2] + smallerNum->m_ptr_int[index3]);
            }
            else if (index2 >= 0)
            {
                sum += biggerNum->m_ptr_int[index2];
            }
            sumTempOutput = sum % 10;
            temp = char(sumTempOutput + 48);

            push2Stack(temp, outputNumberStack);

            sum /= 10;
            index1--;
            index2--;
            index3--;
        }

        index1 = 0;

        while (outputNumberStack != nullptr)
        {
            if (outputNumberStack->num != '0')
                break;

            popFromStack(outputNumberStack);
        }

        if (outputNumberStack == nullptr)
        {
            outputNum.m_ptr_char[0] = '0';
            outputNum.m_ptr_char[1] = '\0';
            return outputNum;
        }

        if (outputNum.m_numberOfEl == 0)
            push2Stack('0', outputNumberStack);

        while (outputNumberStack != nullptr)
        {
            outputNum.m_ptr_char[index1] = outputNumberStack->num;
            outputNumberStack = outputNumberStack->under;
            index1++;
        }
        outputNum.m_ptr_char[index1] = '\0';
    }
    return outputNum;
}

BigNumber BigNumber::sub_numbers_bothPlusOrMinus(BigNumber& secondNum)
{
    const BigNumber* longerNum = this;
    const BigNumber* smallerNum = &secondNum;

    char temp;
    BigNumber outputNum;

    stack_output_num* outputNumberStack = nullptr;
    int index2, index3, index1 = 0;

    index2 = longerNum->m_numberOfEl - 1;
    index3 = smallerNum->m_numberOfEl - 1;
    index1 = longerNum->m_numberOfEl;

    this->rewriteCharArrayToInt();
    secondNum.rewriteCharArrayToInt();

    int subtraction, remember = 0;
    outputNum.m_numberOfEl = longerNum->m_numberOfEl + 1;
    outputNum.m_ptr_int = new int[longerNum->m_numberOfEl + 1];
    outputNum.m_arrLength = longerNum->m_arrLength + 1;

    while (index1 > 0)
    {
        if (index3 >= 0)
        {
            subtraction = ((longerNum->m_ptr_int[index2] - smallerNum->m_ptr_int[index3]) - remember);

            if (subtraction < 0)
            {
                subtraction += 10;
                remember = 1;
            }
            else
            {
                remember = 0;
            }
        }

        else if (index2 >= 0)
        {
            subtraction = longerNum->m_ptr_int[index2] - remember;
            remember = 0;
        }
        temp = char(subtraction + 48);
        push2Stack(temp, outputNumberStack);

        index1--;
        index2--;
        index3--;

    }
    index1 = 0;

    while (outputNumberStack != nullptr)
    {
        if (outputNumberStack->num != '0')
        {
            break;
        }

        popFromStack(outputNumberStack);
        printStack(outputNumberStack);
        outputNum.m_numberOfEl--;
    }

    if (outputNumberStack == nullptr)
    {
        outputNum.m_ptr_char[0] = '0';
        outputNum.m_ptr_char[1] = '\0';
        return outputNum;
    }

    printStack(outputNumberStack);

    while (outputNumberStack != nullptr)
    {
        outputNum.m_ptr_char[index1] = outputNumberStack->num;
        outputNumberStack = outputNumberStack->under;
        index1++;
    }

    outputNum.m_ptr_char[index1] = '\0';
    return outputNum;
}

bool BigNumber::isGreaterThan(BigNumber& secondNum)
{
    bool isEqual = true, temp = true;
    if (secondNum.m_numberOfEl > this->m_numberOfEl)
    {
        return false;
    }
    else if (secondNum.m_numberOfEl < this->m_numberOfEl)
    {
        return true;
    }
    else if (areCharArraysEqual(this->m_ptr_char, secondNum.m_ptr_char, secondNum.m_numberOfEl))
    {
        return false;
    }

    else
    {
        int i = 0;
        while (i < m_numberOfEl)
        {
            if (this->m_ptr_char[i] > secondNum.m_ptr_char[i] && temp == true)
            {
                return true;
            }

            if (this->m_ptr_char[i] < secondNum.m_ptr_char[i])
            {
                temp = false;
            }
            i++;
        }
        if (!temp)
            return false;

        return true;
    }
}


bool BigNumber::isSmallerThan(BigNumber& secondNum)
{
    bool isEqual = true, temp = true;

    if (this->m_numberOfEl < secondNum.m_numberOfEl)
    {
        return true;
    }
    else if (this->m_numberOfEl > secondNum.m_numberOfEl)
    {
        return false;
    }
    else if (areCharArraysEqual(this->m_ptr_char, secondNum.m_ptr_char, secondNum.m_numberOfEl))
    {
        return false;
    }

    else
    {
        int i = 0;
        while (i < m_numberOfEl)
        {
            if (this->m_ptr_char[i] < secondNum.m_ptr_char[i] && temp == true)
            {
                return true;
            }

            if (this->m_ptr_char[i] > secondNum.m_ptr_char[i])
            {
                temp = false;
            }
            i++;
        }
        if (!temp)
            return false;

        return true;
    }
}


bool BigNumber::isMinus()
{
    if (m_ptr_char[0] == '-')
        return true;
    return false;
}

bool areCharArraysEqual(char* first_arr, char* second_arr, int numberOfElements)
{
    for (int i = 0; i < numberOfElements; i++)
    {
        if (first_arr[i] != second_arr[i])
        {
            return false;
        }
    }
    return 1;
}

int findMin(BigNumber* arr, int numberOfArrayElements)
{
    int minNumberIndex = 0;
    BigNumber* temp = &arr[minNumberIndex];

    for (int i = 0; i < numberOfArrayElements; i++)
    {
        if (arr[i].isSmallerThan(*temp))
        {
            temp = &arr[i];
            minNumberIndex = i;
        }
    }
    return minNumberIndex;

}

int findMax(BigNumber* arr, int numberOfArrayElements)
{
    int maxNumberIndex = 0;
    BigNumber* temp = &arr[maxNumberIndex];

    for (int i = 0; i < numberOfArrayElements; i++)
    {
        if (arr[i].isGreaterThan(*temp))
        {
            temp = &arr[i];
            maxNumberIndex = i;
        }
    }
    return maxNumberIndex;
}

