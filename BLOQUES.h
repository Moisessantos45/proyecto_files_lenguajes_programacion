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

void altaBloque()
{
    bloque = capturaBloque();
    if(buscaBloque(Bloque)==-1)
    {
        long pos = escribeBloque(bloque);
        insertaBloque(bloque, pos);
    }
    freeI(bloque);
}

void InsertaBloque(void* nuevoB, long posB)
{
    void* wbAnte= NULL;
    long cabB = entActiva.data;
    if(cabB==-1)
    {
        entActiva.data=posB;
        reescribeEntidad(entActiva, posEntidad);
    }
    else{
        void* bloque=leeBloque(entActiva.data);
        if(comparaBloque(nuevoB, bloque)<0)
        {
            *((long*)nuevoB+0)=cabB;
            reescribeBloque(nuevoB, posB);
            entActiva.data=posB;
            reescribeEntidad(entActiva, posEntActiva);
        }
        else{
            do{
                if(bAnte!=NULL)
                    free(bAnte);
                bAnte=bloque;
                long posBAnte=cabB;
                cabB=getApSig(bloque);
                if(cabB!=-1)
                    bloque=leeBloque(cabB);
            } while(cabB!= -1 && comparaBloque(nuevoB, bloque)>0);
            if(cabB != -1)
            {
                *((long*)(nuevo+0))=cabB;
                reescribeBloque(nuevoB, posB);
            }
            *((long*)(bAnte+0))=posB;
            reescribeBloque(bAnte, posBAnte);
            free(bAnte);
        }
    }
}