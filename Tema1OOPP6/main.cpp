#include <iostream>
#include <cstdlib>

using namespace std;


class vector
{
    int *values;
    int length;
public:
    friend ostream& operator<<(ostream& out, vector& f)
    {
        for(int i=0;i<f.length;i++)
            out<<f.values[i]<<" ";
        out<<endl;
        return out;
    }
    friend istream& operator>>(istream& input, vector& f)
    {
        cout<<"Cate elemente are? ";
        input>>f.length;
        f.values = new int [f.length];
        for(int i=0;i<f.length;i++)
        {
            cout<<"Elementul "<<i<<" = ";
            input>>f.values[i];
            cout<<endl;
        }
        cout<<endl;
        return input;
    }
    ~vector(){delete [] values; length = 0;}
    vector(int x=2)
    {
        values = new int [x]; length = x;
        for(int i=0;i<length;i++)
            values[i]=i+1;
    }
    int return_length(){return length;}
    vector(vector &d, vector &s){d=s;}
    friend vector operator+(vector a,vector b);
    vector& operator=(const vector& a);
    friend class vector_de_vectori;
    int return_value(int i)
    {
        return values[i];
    }
};

vector& vector::operator=(const vector& a)
{
    length=a.length;
    values=new int[a.length];
    for(int i=0;i<a.length;i++)
        values[i]=a.values[i];
    return *this;
}

vector operator+(vector a, vector b)
{
    vector temp(max(a.length,b.length));
    int minLength=min(a.length,b.length);
    for(int i=0;i<minLength;i++)
    {
        temp.values[i]=a.values[i]+b.values[i];
    }
    if(minLength!=a.length)
        for(int i=minLength;i<a.length;i++)
            temp.values[i]=a.values[i];
    else for(int i=minLength;i<b.length;i++)
        temp.values[i]=b.values[i];
    return temp;
}



class vector_de_vectori
{
    int dim, maxlength;
    vector *v;
public:
 friend ostream& operator<<(ostream& out, vector_de_vectori& f)
    {
        for(int i=0;i<f.dim;i++)
            out<<f.v[i];
        out<<endl;
        return out;
    }
    friend istream& operator>>(istream& input, vector_de_vectori& f)
    {
        f.maxlength=0;
        cout<<"Cate linii are ? ";
        input>>f.dim;
        f.v=new vector [f.dim];
        cout<<endl;
        for(int i=0;i<f.dim;i++)
            {
                cout<<"Pentru vectorul "<<i<<endl;
                input>>f.v[i];
                if(f.maxlength<f.v[i].return_length()) f.maxlength=f.v[i].return_length();
            }
        cout<<endl;
        return input;
    }
    ~vector_de_vectori(){delete [] v; maxlength=0; dim=0;}
    vector_de_vectori(int x=2)
    {
        v=new vector [x]; dim=x; maxlength=x;
    }
    vector_de_vectori(int x,vector &s)
    {
        dim=x; v=new vector[x]; maxlength=s.length;
        for(int i=0;i<dim;i++)
        {
            v[i]=s;
        }
    }
    vector_de_vectori(vector_de_vectori &s)
    {
        dim=s.dim;
        maxlength=s.maxlength;
        v=new vector[dim];
        for(int i=0;i<dim;i++)
        {
            v[i]=s.v[i];
        }
    }
    void create_matrix()
    {
        vector a;
        for(int i=0;i<dim;i++)
        {
            if(v[i].length==maxlength)
            {
                a=v[i];
                break;
            }
        }
        vector_de_vectori temp(dim,a);
        for(int i=0;i<dim;i++)
        {
            for(int g=0;g<v[i].length;g++)
            {
                temp.v[i].values[g]=v[i].values[g];
            }
            for(int j=v[i].length;j<maxlength;j++)
            {
                temp.v[i].values[j]=0;
            }
        }
        for(int i=0;i<dim;i++)
            v[i]=temp.v[i];
    }
    friend vector_de_vectori operator+(vector_de_vectori &FirstObject, vector_de_vectori &SecondObject);
    vector_de_vectori& operator=(const vector_de_vectori& a);
};

vector_de_vectori& vector_de_vectori::operator=(const vector_de_vectori& a)
{
    dim=a.dim;
    maxlength=a.maxlength;
    v=new vector[a.dim];
    for(int i=0;i<a.dim;i++)
    {
        v[i]=a.v[i];
    }
    return *this;
}

vector_de_vectori operator+(vector_de_vectori &FirstObject, vector_de_vectori &SecondObject)
{
    vector a(max(FirstObject.maxlength,SecondObject.maxlength));
    vector_de_vectori temp(max(FirstObject.dim,SecondObject.dim),a);
    FirstObject.create_matrix();
    SecondObject.create_matrix();
    int mindim=min(FirstObject.dim,SecondObject.dim);
    for(int i=0;i<mindim;i++)
            temp.v[i]=FirstObject.v[i]+SecondObject.v[i];
    if(mindim!=FirstObject.dim)
        for(int i=mindim;i<FirstObject.dim;i++)
            temp.v[i]=FirstObject.v[i];
    else for(int i=mindim;i<SecondObject.dim;i++)
        temp.v[i]=SecondObject.v[i];
    temp.create_matrix();
    return temp;
}





int main()
{
    /*vector a(3),b(5);
    vector_de_vectori FirstObject(4,a),SecondObject(5,b);
    cin>>FirstObject;
    FirstObject=FirstObject+SecondObject;
    cout<<FirstObject;*/ /// <-just testing
    return 0;
}
