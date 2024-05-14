long buscaBloque(void* bloque)
{
    long cabData = entActiva.data;
    while(cabData!= -1)
    {
        auxB=leeBloque(cabData);
        if(comparaBloques(auxB, bloque)==0)
            return cabData;
        else{
            if(comparaBloques(auxB, bloque) > 0)
                return -1;
            else
                cabData = getApuntadorSig(auxB);
        }
    }
    return -1;
}

void* leeBloque(long dir)
{
    if(dir!=-1)
    {
        void* bloque= malloc(tambloque);
        fseek(f,dir,SEEK_SET);
        fread(bloque, tambloque,1,f);
        return bloque;
    }
    else
        return NULL;
}

long escribeBloque(void *nuevo)
{
    fseek(f, 0, SEEK_END);
    pos=ftell(f);
    fwrite(nuevo,tambloque,1,f);
    return pos;
}

void reescribeBloque(long dir, void* bloque)
{
    fseek(f, dir, SEEK_SET);
    fwrite(bloque, tambloque,1 , f);
}