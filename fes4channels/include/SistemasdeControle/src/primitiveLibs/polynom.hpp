#ifdef testPolynom
    #include "../../../headers/primitiveLibs/polynom.h"
#else
    #include "SistemasdeControle/headers/primitiveLibs/polynom.h"
#endif

template <typename Type> // testada
PolynomHandler::Polynom<Type>::Polynom(const Type &Num)
{
    init(LinAlg::Matrix<Type>(Num),LinAlg::Matrix<Type>(1.0));
}

template <typename Type> //testada
PolynomHandler::Polynom<Type>::Polynom(const LinAlg::Matrix<Type> &Num)
{
    init(Num,LinAlg::Matrix<Type>(1.0));
}

template <typename Type> //testada
PolynomHandler::Polynom<Type>::Polynom(const PolynomHandler::Polynom<Type> &CopyPolynom)
{
    this->num = new Type[CopyPolynom.sizeNum]();
    this->den = new Type[CopyPolynom.sizeDen]();
    this->sizeNum = CopyPolynom.sizeNum;
    this->sizeDen = CopyPolynom.sizeDen;
    this->x = CopyPolynom.x;

    for(unsigned i = 0; i < this->sizeNum; ++i)
        this->num[i] = CopyPolynom.num[i];

    for(unsigned i = 0; i < this->sizeDen; ++i)
        this->den[i] = CopyPolynom.den[i];
}

template <typename Type> template<typename OtherPolynomType>//testada
PolynomHandler::Polynom<Type>::Polynom(const PolynomHandler::Polynom<OtherPolynomType>& otherPolynom)
{
    this->num = new Type[otherPolynom.getNumSize()]();
    this->den = new Type[otherPolynom.getDenSize()]();
    this->sizeNum = otherPolynom.getNumSize();
    this->sizeDen = otherPolynom.getDenSize();
    this->x = otherPolynom.getVar();

    LinAlg::Matrix<OtherPolynomType> NUM = otherPolynom.getNum();
    LinAlg::Matrix<OtherPolynomType> DEN = otherPolynom.getDen();

    for(unsigned i = 0; i < this->sizeNum; ++i)
        this->num[i] = (Type)NUM(0,i);

    for(unsigned i = 0; i < this->sizeDen; ++i)
        this->den[i] = (Type)DEN(0,i);
}

template <typename Type> // testada
PolynomHandler::Polynom<Type>::Polynom(const LinAlg::Matrix<Type> &Num, const LinAlg::Matrix<Type> &Den)
{
    init(Num,Den);
}

template <typename Type> // testada
PolynomHandler::Polynom<Type>::~Polynom()
{
    if(this->sizeNum != 0)
        delete this->num;

    if(this->sizeDen != 0)
        delete this->den;

    this->num = NULL;
    this->den = NULL;

    this->sizeNum = 0;
    this->sizeDen = 0;
}

template <typename Type> //testada
char PolynomHandler::Polynom<Type>::getVar() const
{
    return this->x;
}

template <typename Type> // testada
void PolynomHandler::Polynom<Type>::changeVar(char var)
{
    this->x = var;
}

template <typename Type> //testada
unsigned PolynomHandler::Polynom<Type>::getNumSize() const
{
    return this->sizeNum;
}

template <typename Type> //testada
unsigned PolynomHandler::Polynom<Type>::getDenSize() const
{
    return this->sizeDen;
}

template <typename Type> //testada
LinAlg::Matrix<Type> PolynomHandler::Polynom<Type>::getNum()const
{
    LinAlg::Matrix<Type> ret(1, this->sizeNum);

    for(unsigned i = 0; i < this->sizeNum; ++i)
        ret(0,i) = this->num[i];

    for(unsigned i = 0; i < ret.getNumberOfColumns()-1; ++i){
        if(ret(0,i) == 0){
            ret.removeColumn(0);
            i = -1;
        }
        else
            break;
    }

    return ret;
}

template <typename Type> // testada
LinAlg::Matrix<Type> PolynomHandler::Polynom<Type>::getDen() const
{
    LinAlg::Matrix<Type> ret(1, this->sizeDen);

    for(unsigned i = 0; i < this->sizeDen; ++i)
        ret(0,i) = this->den[i];

    for(unsigned i = 0; i < ret.getNumberOfColumns()-1; ++i){
        if(ret(0,i) == 0){
            ret.removeColumn(0);
            i = -1;
        }
        else
            break;
    }

    return ret;
}

template <typename Type> // testada
void PolynomHandler::Polynom<Type>::setNum(const Type *Num, const unsigned sizenum)
{
    this->num = new Type[sizenum]();
    this->sizeNum = sizenum;

    for (unsigned i = 0; i < sizenum; ++i)
        this->num[i] = Num[i];
}

template <typename Type> //testada
void PolynomHandler::Polynom<Type>::setNum(const LinAlg::Matrix<Type> &Num)
{
    this->num = new Type[Num.getNumberOfColumns()]();
    this->sizeNum = Num.getNumberOfColumns();

    for (unsigned i = 0; i < Num.getNumberOfColumns(); ++i)
        this->num[i] = Num(uint32_t(0),i);
}

template <typename Type> //testada
void PolynomHandler::Polynom<Type>::setDen(const Type *Den, const unsigned sizeden)
{
    this->den = new Type[sizeden]();
    this->sizeDen = sizeden;

    for (unsigned i = 0; i < sizeden; ++i)
        this->den[i] = Den[i];
}

template <typename Type> // testada
void PolynomHandler::Polynom<Type>::setDen(const LinAlg::Matrix<Type> &Den)
{
    this->den = new Type[Den.getNumberOfColumns()]();
    this->sizeDen = Den.getNumberOfColumns();

    for (unsigned i = 0; i < Den.getNumberOfColumns(); ++i)
        this->den[i] = Den(uint32_t(0),i);
}

template <typename Type> // testada
PolynomHandler::Polynom<Type>& PolynomHandler::Polynom<Type>::operator= (const PolynomHandler::Polynom<Type>& OtherPolynom)
{
    this->setDen(OtherPolynom.den, OtherPolynom.sizeDen);
    this->setNum(OtherPolynom.num, OtherPolynom.sizeNum);
    this->x = OtherPolynom.x;

    return *this;
}

template <typename Type> template<typename OtherPolynomType> // testada
PolynomHandler::Polynom<Type>& PolynomHandler::Polynom<Type>::operator= (const PolynomHandler::Polynom<OtherPolynomType>& OtherPolynom)
{
    this->setDen(OtherPolynom.getDen());
    this->setNum(OtherPolynom.getNum());
    this->changeVar(OtherPolynom.getVar());

    return *this;
}

template <typename Type> //Testada
PolynomHandler::Polynom<Type>& PolynomHandler::Polynom<Type>::operator+= (const Type& scalar)
{
    if(scalar == 0)
        return *this;

    PolynomHandler::Polynom<Type> ret(scalar);
    ret.setNum(this->den, this->sizeDen);
    ret.setDen(this->den, this->sizeDen);
    for(unsigned i = 0; i < ret.sizeNum; ++i)
        ret.num[i] = ret.num[i]*scalar;

    this->num = PolynomHandler::SumPoly<Type>(this->num, ret.num, this->sizeNum, ret.sizeNum);

    unsigned max = this->sizeNum, min = this->sizeDen;
    if(min > max)
    {
        max = this->sizeDen; min = this->sizeNum;
    }
    this->sizeNum = max;

    return *this;
}

template <typename Type> template<typename RightType>//testada
PolynomHandler::Polynom<Type>& PolynomHandler::Polynom<Type>::operator+= (const PolynomHandler::Polynom<RightType>& rhs)
{
    PolynomHandler::Polynom<Type> ret;
    unsigned max;

   if(VefDen(this->den, rhs.den, this->sizeDen, rhs.sizeDen))
   {
       ret.num = SumPoly(this->num, rhs.num, this->sizeNum, rhs.sizeNum);
       ret.setDen(rhs.den, rhs.sizeDen);

       max = this->sizeNum;

       if (max < rhs.sizeNum)
           max = rhs.sizeNum;

       ret.sizeNum = max;
   }
   else
   {
       ret.num = SumPoly(MultPoly(rhs.den, this->num, rhs.sizeDen, this->sizeNum),MultPoly(rhs.num, this->den, rhs.sizeNum, this->sizeDen), (rhs.sizeDen + this->sizeNum - 1),(rhs.sizeNum + this->sizeDen - 1));
       ret.den = MultPoly(this->den, rhs.den, this->sizeDen, rhs.sizeDen);

       max = (rhs.sizeDen + this->sizeNum - 1);

       if(max < (rhs.sizeNum + this->sizeDen - 1))
           max = (rhs.sizeNum + this->sizeDen - 1);

       ret.sizeNum = max;
       ret.sizeDen = this->sizeDen + rhs.sizeDen - 1;
   }

   *this = ret;
   return *this;
}

template <typename Type> //Testada
PolynomHandler::Polynom<Type>& PolynomHandler::Polynom<Type>::operator-= (const Type& rhs)
{
    if(rhs == 0)
        return *this;

    *this += (-rhs);
    return *this;
}

template <typename Type> template<typename RightType>
PolynomHandler::Polynom<Type>& PolynomHandler::Polynom<Type>::operator-= (const PolynomHandler::Polynom<RightType>& rhs)
{
    *this += (-rhs);
    return *this;
}

template <typename Type>
PolynomHandler::Polynom<Type>& PolynomHandler::Polynom<Type>::operator*= (const Type& rhs /*scalar*/)
{
    for (unsigned i = 0; i < this->sizeNum; ++i)
        this->num[i] = rhs*this->num[i];

    return *this;
}

template <typename Type> template<typename RightType>
PolynomHandler::Polynom<Type>& PolynomHandler::Polynom<Type>::operator*= (const PolynomHandler::Polynom<RightType>& rhs)
{
    this->num = MultPoly(this->num, rhs.num, this->sizeNum, rhs.sizeNum);
    this->den = MultPoly(this->den, rhs.den, this->sizeDen, rhs.sizeDen);
    this->sizeNum = this->sizeNum + rhs.sizeNum - 1;
    this->sizeDen = this->sizeDen + rhs.sizeDen - 1;
    return *this;
}

template <typename Type>
PolynomHandler::Polynom<Type>& PolynomHandler::Polynom<Type>::operator/= (const Type& rhs /*scalar*/)
{
    *this *= (1/rhs);
    return *this;
}

template <typename Type> template<typename RightType>
PolynomHandler::Polynom<Type>& PolynomHandler::Polynom<Type>::operator/= (const PolynomHandler::Polynom<RightType>& rhs)
{
    PolynomHandler::Polynom<Type> ret;

    ret.setDen(rhs.num, rhs.sizeNum);
    ret.setNum(rhs.den, rhs.sizeDen);
    *this *= ret;
    return *this;
}

template <typename Type>
bool PolynomHandler::Polynom<Type>::operator==  (const PolynomHandler::Polynom<Type>& pol)
{
    if(this->sizeDen == pol.sizeDen && this->sizeNum == pol.sizeNum)
    {
        for(unsigned i = 0; i < this->sizeDen; ++i)
            if(this->den[i] != pol.den[i])
                return false;
        for(unsigned i = 0; i < this->sizeNum; ++i)
            if(this->num[i] != pol.num[i])
                return false;
    }
    else
    {
        return false;
    }
    return true;
}

template <typename Type>
PolynomHandler::Polynom<Type>& PolynomHandler::Polynom<Type>::operator^= (int exp)
{
    PolynomHandler::Polynom<Type> ret, temp;

    if(exp != 0)
    {
        if(exp < 0)
        {
            ret.setNum(this->den, this->sizeDen);
            ret.setDen(this->num, this->sizeNum);
            exp = -exp;
        }
        else
        {
            ret = *this;
        }
        temp = ret;
        for (int i = 1; i < exp; ++i){
            ret *= temp;
        }
    }
    else
    {
        ret.num = new Type[1]();
        ret.num[0] = 1;
        ret.den = new Type[1]();
        ret.den[0] = 1;
        ret.sizeNum = 1;
        ret.sizeDen = 1;
    }
    *this = ret;
    return *this;
}

template <typename Type>
void PolynomHandler::Polynom<Type>::init(const LinAlg::Matrix<Type> &Num, const LinAlg::Matrix<Type> &Den)
{
    using namespace std;

    this->sizeNum = Num.getNumberOfColumns();
    //this->num = initPointer<Type>(Num.getNumberOfColumns());
    this->num = new Type[Num.getNumberOfColumns()]();
    for (unsigned i = 0; i < Num.getNumberOfColumns(); ++i)
        this->num[i] = (Type) Num(uint32_t(0), i);

    this->sizeDen = Den.getNumberOfColumns();
    this->den = new Type[Den.getNumberOfColumns()]();
    for (unsigned i = 0; i < Den.getNumberOfColumns(); ++i)
        this->den[i] = (Type) Den(uint32_t(0) , i);
    this->x = 'x';
}

template <typename Type>
bool PolynomHandler::Polynom<Type>::isZero()
{
    unsigned counter = 0;
    for(unsigned i = 0; i < this->sizeNum; ++i)
        if(this->num[i] != 0)
            counter++;

    if(counter == this->sizeNum)
        return 0;
    return 1;
}

template<typename PolynomType>
PolynomHandler::Polynom<PolynomType> PolynomHandler::operator- (PolynomHandler::Polynom<PolynomType> rhs)
{
    rhs.setNum(-rhs.getNum());
    return rhs;
}

template <typename PolynomType>
std::ostream& PolynomHandler::operator<< (std::ostream& output, PolynomHandler::Polynom<PolynomType> rhs)
{
    std::string polyNum = PolynomHandler::printSmallPolynom<PolynomType>(rhs.getNum(), rhs.getVar());
    std::string polyDen = PolynomHandler::printSmallPolynom<PolynomType>(rhs.getDen(), rhs.getVar());
    std::string numSpace, denSpace, midLine;

    unsigned maxSize = polyNum.length();
    if(maxSize < polyDen.length())
        maxSize = polyDen.length();

    maxSize += 6;

    for(unsigned i = 0; i < unsigned(fabs((maxSize - polyNum.length())/2)); ++i)
        numSpace += ' ';
    for(unsigned i = 0; i < maxSize; ++i)
        midLine += '-';
    for(unsigned i = 0; i < unsigned(fabs((maxSize - polyDen.length())/2)); ++i)
        denSpace += ' ';

    LinAlg::Matrix<PolynomType> temp = rhs.getDen();

    unsigned counter = 0;
    for(unsigned i = 0; i < temp.getNumberOfColumns(); ++i)
        if(temp(0,i) != 0)
            break;
        else
            ++counter;
    if(counter == temp.getNumberOfColumns())
    {
        output << "Polinomio tem denominador zero!!";
        return output;
    }

    output << numSpace << polyNum << numSpace << '\n';

    counter = 0;
    for(unsigned i = 0; i < temp.getNumberOfColumns(); ++i)
        if(temp(0,i) != 1)
            break;
        else
            ++counter;
    if(counter == temp.getNumberOfColumns())
        return output;

    output << midLine << '\n';
    output << denSpace << polyDen << denSpace << '\n';

    return output;
}

template<typename Type>
std::string& PolynomHandler::operator<< (std::string& output, PolynomHandler::Polynom<Type> rhs)
{
    std::stringstream ss;
    ss << rhs;
    output = ss.str();
    return output;
}

template<typename ScalarType, typename PolynomType>
PolynomHandler::Polynom<PolynomType> PolynomHandler::operator/ (ScalarType lhs, PolynomHandler::Polynom<PolynomType> rhs) {
    LinAlg::Matrix<PolynomType> num = rhs.getNum(), den = rhs.getDen();
    rhs.setNum(den);
    rhs.setDen(num);
    return rhs *= lhs;
}

template<typename PolynomType>
LinAlg::Matrix< PolynomHandler::Polynom<PolynomType> > PolynomHandler::operator/ (LinAlg::Matrix< PolynomHandler::Polynom<PolynomType> > lhs, const PolynomHandler::Polynom<PolynomType> &rhs)
{
    for(unsigned i = 0; i < lhs.getNumberOfRows(); ++i)
        for(unsigned j = 0; j < lhs.getNumberOfColumns(); ++j)
            lhs(i,j) /= rhs;
    return lhs;
}

template <typename Type>
LinAlg::Matrix<Type> PolynomHandler::zerosElimination(LinAlg::Matrix<Type> smallPoly)
{
    for(unsigned i = 0; i < smallPoly.getNumberOfColumns(); ++i){
        if(smallPoly(0,i) == 0){
            smallPoly.removeColumn(0);
            i =0;
        }
        else
            break;
    }
    return smallPoly;
}

template <typename Type>
LinAlg::Matrix<Type> PolynomHandler::derivate(const LinAlg::Matrix<Type> &smallPoly)
{
    if(smallPoly.getNumberOfColumns() > 1)
    {
        LinAlg::Matrix<Type> derivatedSmallPoly(smallPoly.getNumberOfRows(),smallPoly.getNumberOfColumns()-1);
        unsigned count = 0;
        for(int i = smallPoly.getNumberOfColumns()-1; i >= 0; --i)
        {
            derivatedSmallPoly(0,count) = smallPoly(0,count)*i;
            count++;
        }
        return derivatedSmallPoly;
    }
    else if(smallPoly.getNumberOfColumns() == 1)
        return LinAlg::Matrix<Type>(0.0);
    else
        return LinAlg::Matrix<Type>();
}

template <typename Type>
PolynomHandler::Polynom<Type> PolynomHandler::derivate(const PolynomHandler::Polynom<Type> &rhs)
{
    LinAlg::Matrix<Type> num = rhs.getNum();
    LinAlg::Matrix<Type> den = rhs.getDen();
    LinAlg::Matrix<Type> numDerivate = derivate(rhs.getNum());
    LinAlg::Matrix<Type> denDerivate = derivate(rhs.getDen());
    Polynom<Type> f(num,"1"), df(numDerivate,"1"),
                  g(den,"1"), dg(denDerivate,"1");
    return (df*g-f*dg)/(g*g);
}

template<typename Type>
std::string PolynomHandler::printSmallPolynom(LinAlg::Matrix<Type> rhs, const char &variable)
{
    std::ostringstream ret;
    rhs = zerosElimination(rhs);

    const char plusSignal  = '+';
    const char minusSignal = '-';
    unsigned Size = rhs.getNumberOfColumns()-1;

    if(Size == -1)
        return ret.str();

    for(unsigned i = 0; i <= Size; ++i)
    {
        if(i != 0 && rhs(0,i) > 0 && Size != 0)
        {
            ret << plusSignal << ' ';
        }
        else if(rhs(0,i) < 0)
        {
            ret << minusSignal << ' ';
        }

        if(((rhs(0,i) != 1) && (rhs(0,i) > 0)) || ((i == Size) && (rhs(0,i) > 0)))
            ret << std::setw(2*coutPrecision+1) << std::setprecision(coutPrecision) << std::fixed << rhs(0,i);
        else if((rhs(0,i) != -1 && rhs(0,i) < 0)|| ((i == Size) && (rhs(0,i) < 0)))
            ret << std::setw(2*coutPrecision+1) << std::setprecision(coutPrecision) << std::fixed << -rhs(0,i);

        if(Size-i > 0 && rhs(0,i) != 0)
        {
            ret << variable;
            if(i != Size-1)
            {
                ret << '^';
                ret << Size-i;
            }
        }

        ret << ' ';
    }

    return ret.str();
}

template <typename Type>
bool PolynomHandler::VefDen(const Type *den1, const Type *den2, const unsigned &sizeden1, const unsigned &sizeden2)
{
    bool vef = true;

    if (sizeden1 != sizeden2)
        vef = false;
    else
    {
        for (unsigned i = 0; i < sizeden1; ++i)
            if (den1[i] != den2[i])
            {
                vef = false;
                break;
            }
    }

    return vef;
}

//template <typename Type>
//bool PolynomHandler::isDivisible(const Type *lhs, const Type *rhs, const unsigned &lhsSize, const unsigned &rhsSize)
//{

//}

template <typename Type> //testada
Type* PolynomHandler::SumPoly(const Type *lhs, const Type *rhs, const unsigned &lhsSize, const unsigned &rhsSize)
{
    unsigned min = lhsSize, max = rhsSize; Type *ret = new Type[max+1]();
    for(unsigned i = 0; i <= rhsSize; ++i)
        ret[i] = rhs[i];

    if(min > rhsSize)
    {
        min = rhsSize; max = lhsSize; ret = new Type[max+1]();
        for(unsigned i = 0; i <= rhsSize; ++i)
            ret[i] = lhs[i];
    }

    for (unsigned i = 1; i <= min; ++i)
        ret[max - i] =  lhs[lhsSize - i] + rhs[rhsSize - i];

    return ret;
}

template <class Type> // verificar
Type *PolynomHandler::MultPoly(const Type *lhs, const Type *rhs, const unsigned &lhsSize, const unsigned &rhsSize)
{
    Type *ret = new Type [lhsSize+rhsSize-1]();

    for(unsigned i = 0; i < lhsSize; ++i)
        for(unsigned j = 0; j < rhsSize; ++j)
        {
            ret[i+j] += lhs[i]*rhs[j];
        }

    return ret;
}

template <class Type> // com defeito
LinAlg::Matrix<Type> PolynomHandler::MultPoly(const LinAlg::Matrix<Type> &lhs, const LinAlg::Matrix<Type> &rhs)
{
    unsigned lhsSize = lhs.getNumberOfColumns();
    unsigned rhsSize = rhs.getNumberOfColumns();
    LinAlg::Matrix<Type>ret(1,lhsSize+rhsSize-1);

    for(unsigned i = 0; i < lhsSize; ++i)
        for(unsigned j = 0; j < rhsSize; ++j)
        {
            ret(0,i+j) += lhs(0,i)*rhs(0,j);
        }

    return ret;
}

template <class Type>//falta testar
PolynomHandler::Polynom<Type> PolynomHandler::simplify(const PolynomHandler::Polynom<Type> &P)
{
    LinAlg::Matrix<Type> num = P.getNum();
    LinAlg::Matrix<Type> den = P.getDen();

    LinAlg::Matrix<Type> numRoots = rootsNewtonBairstow<long double>(num,1e-10);
    LinAlg::Matrix<Type> denRoots = rootsNewtonBairstow<long double>(den,1e-10);

    unsigned counter = 0;
    for(unsigned i = 0; i < numRoots.getNumberOfRows(); ++i){
        for(unsigned j = 0; j < denRoots.getNumberOfRows(); ++j)
            if(fabs(denRoots(j,0) - numRoots(i,0)) < 0.05 && fabs(denRoots(j,1) - numRoots(i,1)) < 0.05)
            {
                numRoots.removeRow(i);
//                numRoots.removeRow(i - counter);
                denRoots.removeRow(j);
                ++counter;
                i = -1;
                break;
            }
        if(i == numRoots.getNumberOfRows() && counter == 0)
            return Polynom<Type>(num,den);
    }

    LinAlg::Matrix<Type> numPol = Root2Poly(numRoots);
    if(numPol.getNumberOfColumns() == 0)
        numPol = LinAlg::Matrix<Type>(num(0,0));
    else
        numPol *= num(0,0);
    LinAlg::Matrix<Type> denPol = Root2Poly(denRoots);
    if(denPol.getNumberOfColumns() == 0)
        denPol = LinAlg::Matrix<Type>(den(0,0));
    else
        denPol *= den(0,0);

    return Polynom<Type>(numPol,denPol);
}

template<class Type>
LinAlg::Matrix<Type> PolynomHandler::Roots(LinAlg::Matrix<Type> smallPoly)
{   
    unsigned zeroRoots;
    for(zeroRoots = 0; zeroRoots < smallPoly.getNumberOfColumns(); ++zeroRoots){
        if(smallPoly(1,smallPoly.getNumberOfColumns() - zeroRoots) == 0){
            smallPoly.removeColumn(smallPoly.getNumberOfColumns() - zeroRoots);
        }
        else
            break;
    }
    for(unsigned i = 0; i < smallPoly.getNumberOfColumns()-1; ++i){
        if(smallPoly(0,i) == 0)
            smallPoly.removeColumn(0);
        else
            break;
    }

    //const Type *num;
    if(smallPoly.getNumberOfColumns() <= 1)
        return LinAlg::Matrix<Type>();
    else if(smallPoly.getNumberOfColumns() == 2){
        LinAlg::Matrix<Type> root(1,2);
        root(0,0) = -smallPoly(0,1)/smallPoly(0,0);
        return root;
    }
    else if(smallPoly.getNumberOfColumns() == 3){
        LinAlg::Matrix<Type> mat(2,2);
        double a = smallPoly(0,0),b = smallPoly(0,1),c = smallPoly(0,2);
        double delt = (b*b) - 4 * c * a;

        if(delt < 0){
            mat(1,1) = -b / 2 * a;
            mat(1,2) = sqrt(-delt) / 2 * a;
            mat(2,1) = -b / 2 * a;
            mat(2,2) = -sqrt(-delt) / 2 * a;
        }else{
           mat(1,1) = (-b + sqrt(delt)) / 2 * a;
           mat(2,1) = (-b - sqrt(delt)) / 2 * a;
        }

        return LinAlg::Zeros<Type>(zeroRoots,2)||mat;
    }
    else
    {
        LinAlg::Matrix<Type>root;
        unsigned numSize = smallPoly.getNumberOfColumns();
        LinAlg::Matrix<Type> poly_Monic(1,numSize-1);
        for(unsigned j = 1; j < numSize; ++j)
        {
            poly_Monic(0,j) = -smallPoly(0,j)/smallPoly(0,0);
        }

        root = poly_Monic||(LinAlg::Eye<Type> (numSize-2) | LinAlg::Zeros<Type> (numSize-2,1));
//        std::cout << "roots" << LinAlg::EigenValues(root);
        LinAlg::Matrix<Type> Ava, Ave; *(Ava, Ave) = LinAlg::eigenValues(root);
        return LinAlg::Zeros<Type>(zeroRoots,2)||Ava;
    }
}

template<typename Type>
LinAlg::Matrix<Type> PolynomHandler::rootsNewtonBairstow(LinAlg::Matrix<Type> smallPoly, Type tolerance)
{
    LinAlg::Matrix<Type> ret;

    while(smallPoly.getNumberOfColumns() > 3){
        Type alfa = -0.01, beta = 0.01;
        LinAlg::Matrix<Type> b(1,smallPoly.getNumberOfColumns()), c(1,smallPoly.getNumberOfColumns()-1);
        unsigned n;
        unsigned i = 0;
        while (i < 5000)
        {
            b(0,0) = smallPoly(0,0);
            b(0,1) = smallPoly(0,1)+alfa*b(0,0);

            for (n = 2; n < b.getNumberOfColumns(); ++n)
               b(0,n) = smallPoly(0,n)+alfa*b(0,n-1)+ beta*b(0,n-2);

            c(0,0) = b(0,0);
            c(0,1) = b(0,1)+alfa*c(0,0);
            for (n = 2; n < c.getNumberOfColumns(); ++n)
                c(0,n) = b(0,n)+alfa*c(0,n-1)+ beta*c(0,n-2);

            n = b.getNumberOfColumns()-1;
            if(fabsl(b(0,n))+fabsl(b(0,n-1)) <= tolerance)
                break;

            alfa -= (1/((c(0,n-2)*(c(0,n-2)))-c(0,n-1)*c(0,n-3)))*(c(0,n-2)*b(0,n-1)-c(0,n-3)*b(0,n));
            beta -= (1/((c(0,n-2)*(c(0,n-2)))-c(0,n-1)*c(0,n-3)))*(c(0,n-2)*b(0,n)-c(0,n-1)*b(0,n-1));
            ++i;
        }

        LinAlg::Matrix<Type> roots(2,2);
        Type delta = alfa*alfa + 4*beta;
        if(delta >= 0 )
        {
            roots(0,0) = (alfa + sqrt(delta))/2;
            roots(0,1) = (alfa - sqrt(delta))/2;
        }
        else
        {
            roots(0,0) = alfa/2;
            roots(0,1) = alfa/2;
            roots(1,0) = sqrt(-delta)/2;
            roots(1,1) = -sqrt(-delta)/2;
        }
        ret = ret|roots;
        smallPoly = b(0,from(0)-->b.getNumberOfColumns()-3);
    }

    if(smallPoly.getNumberOfColumns() == 2)
    {
        LinAlg::Matrix<Type> root(2,1);
        root(0,0) = -smallPoly(0,1)/smallPoly(0,0);
        ret = ret|root;
    }
    else
    {
        LinAlg::Matrix<Type> roots(2,2);
        Type delta = smallPoly(0,1)*smallPoly(0,1) - 4*smallPoly(0,0)*smallPoly(0,2);
        if(delta >= 0 )
        {
            roots(0,0) = (-smallPoly(0,1) + sqrt(delta))/(2*smallPoly(0,0));
            roots(0,1) = (-smallPoly(0,1) - sqrt(delta))/(2*smallPoly(0,0));
        }
        else
        {
            roots(0,0) = -smallPoly(0,1)/(2*smallPoly(0,0));
            roots(0,1) = -smallPoly(0,1)/(2*smallPoly(0,0));
            roots(1,0) = sqrt(-delta)/(2*smallPoly(0,0));
            roots(1,1) = -sqrt(-delta)/(2*smallPoly(0,0));
        }
        ret = ret|roots;
    }

    return ~ret;
}

template <typename Type>
LinAlg::Matrix<Type> PolynomHandler::Root2Poly(const LinAlg::Matrix<Type> &root)
{
    if(root.getNumberOfColumns() == 0)
        return LinAlg::Matrix<Type>();

    unsigned n = root.getNumberOfRows();
    LinAlg::Matrix<Type> ret(1,n+1);
    std::complex<Type> *tempPoly = new std::complex<Type> [2]();
    tempPoly[0] = 1;
    tempPoly[1] = std::complex<Type>(-root(0,0),-root(0,1));
    std::complex<Type> * tempRoot = new std::complex<Type>[2]();

    unsigned sizeTempPoly = 2;
    tempRoot[0] = 1;
    for(unsigned i = 1; i < n ; ++i)
    {
        tempRoot[1] = std::complex<Type>(-root(i,0),-root(i,1));//apos o templade entre (real,imaginario) atribuição
        tempPoly = PolynomHandler::MultPoly(tempPoly,tempRoot,sizeTempPoly,2);
        sizeTempPoly++;
    }
    for(unsigned i = 0; i < sizeTempPoly; ++i)
    {
        ret(0,i) = tempPoly[i].real();
    }
    return ret;
}

template <typename Type>
bool PolynomHandler::rootsContainRoot(const Type &root, const LinAlg::Matrix<Type> &roots)
{
    for(unsigned i = 0; i < roots.getNumberOfRows(); ++i)
    {
        if(root == roots(0,i))
            return 1;
    }
    return 0;
}
