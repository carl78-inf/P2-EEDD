#ifndef CENTRO_H
#define CENTRO_H



class Centro
{
    private:
        int id_centro;    //ID único del Centro de 3 cifras (100-999)
        string localidad; //Localidad donde se encuentra el Centro

    public:
        Centro();
        virtual ~Centro();
};

#endif // CENTRO_H
