#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <stdexcept>

template<class T>
class Matrix{
    public:
        Matrix();
        Matrix(const unsigned&,const unsigned&,bool create=true);
        Matrix(const Matrix<T>&,bool own=true);
        Matrix(const std::vector<T>&,bool);
        Matrix<T> &operator=(const Matrix<T>&);
        std::vector<T> &operator[](const unsigned&)const;
        friend std::ostream &operator<<(std::ostream&out,const Matrix<T>&M){
            for(unsigned i=0;i<M.row;i++){
                for(unsigned j=0;j<M.col;j++){
                    out<<(*M.matrix)[i][j]<<' ';
                }
                out<<'\n';
            }
            return out;
        }
        void rFill();
        static void transfer(Matrix<T>&,Matrix<T>&);
        static void swapOwners(Matrix &,Matrix &);
        Matrix<T> &operator+=(const Matrix&);
        Matrix<T> &operator-=(const Matrix&);
        Matrix<T> &operator*=(const Matrix&);
        Matrix<T> &operator*=(const T&);
        Matrix<T> &operator/=(const T&);

        unsigned getCol()const{
            return col;
        }
        unsigned getRow()const{
            return row;
        }
        void setCol(const unsigned& col ){
            this->col=col;
        }
        void setRow(const unsigned& row){
            this->row=row;
        }
        bool ownsMatrix()const{
            return isOwning;
        }
        bool hasMatrix()const{
            return isCreated;
        }
        ~Matrix();

    protected:

    private:
        mutable bool isOwning;
        bool isCreated;
        unsigned row,col;
        std::vector<std::vector<T> > *matrix;
};

template<class T> Matrix<T> operator+(Matrix<T>,const Matrix<T>&);
template<class T> Matrix<T> operator-(Matrix<T>,const Matrix<T>&);
template<class T> Matrix<T> operator*(Matrix<T>,const Matrix<T>&);
/**
=================================================================

END OF DECLARATIONS

=================================================================
*/

template<class T>
Matrix<T>::Matrix(){
    isOwning=false;
    isCreated=false;
    col = 0;
    row = 0;
    matrix = 0;
}

template<class T>
Matrix<T>::Matrix(const unsigned&row,const unsigned&col,bool create){
    this->row=row;
    this->col=col;
    if(create){
        matrix = new std::vector<std::vector<T> >;
        for(unsigned i=0;i<row;i++){
            matrix->push_back(std::vector<T>(this->col));
        }
    }else{
        matrix = 0;
    }
    isOwning = create;
    isCreated = create;
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>&other,bool own){
    this->row = other.row;
    this->col = other.col;
    if(own){
        matrix = new std::vector<std::vector<T> >;
        (*matrix)=(*other.matrix);
    }else{
        matrix = other.matrix;
    }
    isCreated = own;
    isOwning = own;
}

template<class T>
Matrix<T>::Matrix(const std::vector<T>&in,bool toRow){
    if(toRow){
        this->col=in.size();
        this->row=1;
        matrix = new std::vector<std::vector<T> >(1);
        (*matrix)[0]=in;
    }else{
        this->row=in.size();
        this->col=1;
        matrix = new std::vector<std::vector<T> >;
        for(unsigned i=0;i<row;i++){
            matrix->push_back(std::vector<T>(1));
            (*matrix)[i][0]=in[i];
        }
    }
    isOwning = true;
    isCreated= true;
}

template<class T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T>&other){
    if(this!=&other){
        if(isOwning){
            delete matrix;
        }
        matrix=0;
        this->row=other.row;
        this->col=other.col;
        matrix = new std::vector<std::vector<T> >;
        (*matrix)=(*other.matrix);
        isOwning=true;
        isCreated=other.isCreated;
    }
    return *this;
}

template<class T>
std::vector<T> &Matrix<T>::operator[](const unsigned&index)const{
    if(index>=row){
        std::invalid_argument("index out of bounds");
    }
    return (*matrix)[index];
}

template<class T>
void Matrix<T>::rFill(){
    for(unsigned i=0;i<row;i++){
        for(unsigned j=0;j<col;j++){
            (*matrix)[i][j]=rand()%10;
        }
    }
}

template<class T>
void Matrix<T>::transfer(Matrix<T>&dst,Matrix<T>&src){
    if(dst.isOwning){
        delete dst.matrix;
        dst.matrix=0;
    }
    dst.col=src.col;
    dst.row=src.row;
    dst.matrix = src.matrix;
    dst.isOwning=true;
    src.isOwning=false;
}

template<class T>
void Matrix<T>::swapOwners(Matrix &_old,Matrix &_new){
    if(&_old!=&_new){
        std::swap(_old.isOwning,_new.isOwning);
    }
}

template<class T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T>&other){
    if(this->col!=other.col||this->row!=other.row){
        throw std::invalid_argument("Dimensions not same!\n");
        return *this;
    }
    for(unsigned i=0;i<row;i++){
        for(unsigned j=0;j<col;j++){
            (*this->matrix)[i][j]+=(*other.matrix)[i][j];
        }
    }
    return *this;
}
template<class T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T>&other){
    if(this->col!=other.col||this->row!=other.row){
        throw std::invalid_argument("Dimensions not same(+)!\n");
        return *this;
    }
    for(unsigned i=0;i<row;i++){
        for(unsigned j=0;j<col;j++){
            (*this->matrix)[i][j]-=(*other.matrix)[i][j];
        }
    }
    return *this;
}
template<class T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T>&other){
    if(col!=other.row){
        throw std::invalid_argument("Dimensions not same(*)!\n");
        return *this;
    }
    Matrix temp(row,other.col);

    for(unsigned i=0;i<row;i++){
        for(unsigned j=0;j<other.col;j++){
            T sum = 0;
            for(unsigned k=0;k<col;k++){
                sum+=(*matrix)[i][k]*(*other.matrix)[k][j];
            }
            (*temp.matrix)[i][j]=sum;
        }
    }
    //(*matrix)=(*temp.matrix);
    row = temp.row;
    col = temp.col;
    delete matrix;
    matrix = temp.matrix;
    isOwning = true;
    temp.isOwning=false;
    return *this;
}

template<class T>
Matrix<T> &Matrix<T>::operator*=(const T&scalar){
    for(unsigned i=0;i<row;i++){
        for(unsigned j=0;j<col;j++){
            (*this->matrix)[i][j]*=scalar;
        }
    }
    return *this;
}

template<class T>
Matrix<T> &Matrix<T>::operator/=(const T&scalar){
    for(unsigned i=0;i<row;i++){
            for(unsigned j=0;j<col;j++){
                (*this->matrix)[i][j]/=scalar;
            }
    }
    return *this;
}

template<class T>
Matrix<T>::~Matrix(){
    if(isOwning){
        delete matrix;
    }
}

template<class T> Matrix<T> operator+(Matrix<T> left,const Matrix<T>&right){
    return left+=right;
}
template<class T> Matrix<T> operator-(Matrix<T> left,const Matrix<T>&right){
    return left-=right;
}
template<class T> Matrix<T> operator*(Matrix<T> left,const Matrix<T>&right){
    return left*=right;
}

#endif // MATRIX_H
