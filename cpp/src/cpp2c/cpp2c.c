#include <stdlib.h> /* malloc */
#include <stdio.h> /*printf*/

#include "cpp2c.h"

/******************************* Struct Definition *******************************/

struct vtable
{
    void (*Dtor)(void *);
    void (*Display)(void const *);
};

struct vtable_mb
{
    void (*Dtor)(void *);
    void (*Display)(void const *);
    void (*Wash)(void *, int);
};

struct PublicTransport
{
    vtable_t *vptr;
    void (*PrintCount)(void);
    int m_license_plate;
};

struct Minibus
{
    vtable_mb_t *vptr;
    PublicTransport_t m_superclass;
    int m_numSeats;
};

struct Taxi
{
    vtable_t *vptr;
    PublicTransport_t m_superclass;
};

struct SpecialTaxi
{
    vtable_t *vptr;
    Taxi_t m_superclass;
};

/******************************* Static Data Memb ******************************/

static int PublicTransport_s_count = 0;

/******************************** Static SizeOf ********************************/

size_t GetSizeof(typeid_t type)
{
    static size_t types_size[NUM_OF_TYPE] = {   sizeof(PublicTransport_t), 
                                                sizeof(Minibus_t), 
                                                sizeof(Taxi_t), 
                                                sizeof(SpecialTaxi_t)
                                            };
    return (types_size[type]);
}

/******************************** Static V-Table *******************************/

vtable_mb_t *GetVtableMB()
{
    static vtable_mb_t g_minibus_vtble = {MinibusDestroy, MinibusDisplay, Wash};
    return (&g_minibus_vtble);
}


vtable_t *GetVtable(typeid_t type)
{
    static vtable_t g_publictransport_vtble = { PublicTransportDestroy, 
                                                PublicTransportDisplay
                                                };

    static vtable_t g_taxi_vtble = {    TaxiDestroy, 
                                        TaxiDisplay
                                    };

    static vtable_t g_staxi_vtble = {   SpecialTaxiDestroy, 
                                        SpecialTaxiDisplay
                                    };

    vtable_t *return_table = NULL;

    switch (type)
    {
    case PUBLICTRANSPORT:
    {
        return_table = &g_publictransport_vtble;
        break;
    }
    case TAXI:
    {
        return_table = &g_taxi_vtble;
        break;
    }
    case SPECIALTAXI:
    {
        return_table = &g_staxi_vtble;
        break;
    }
    default:
    {
        return_table = &g_publictransport_vtble;
        break;
    }
    }

    return (return_table);
}

/**************************** allocet *******************************/

void *Allocet(void **location, size_t size_of_alloc)
{
    *location = malloc(size_of_alloc);

    return (location);
}

void *Init(void **obj_ptr, typeid_t flag)
{
    switch (flag)
    {
    case PUBLICTRANSPORT:
    {
        PublicTransportCreat((PublicTransport_t *)(*obj_ptr));
        break;
    }
    case MINIBUS:
    {
        MinibusCreate((Minibus_t *)*obj_ptr);
        break;
    }
    case TAXI:
    {
        TaxiCreate((Taxi_t *)*obj_ptr);
        break;
    }
    case SPECIALTAXI:
    {
        SpecialTaxiCreate((SpecialTaxi_t *)*obj_ptr);
        break;
    }
    default:
    {
        break;
    }
    }

    return (*obj_ptr);
}
/**************************** general *******************************/

static void PrintCount()
{
    printf("s_count: %d\n", PublicTransport_s_count);
}

void PrintInfoPublicTransport(PublicTransport_t *pt)
{
    pt->vptr->Display(pt);
    return;
}

void PrintInfoVoid()
{
    PrintCount();
    return;
}

void PrintInfoMinibus(Minibus_t *mb)
{
    mb->vptr->Wash(mb, 3);
    return;
}

PublicTransport_t PrintInfoInt(int i)
{
    UNUSED(i);
    Minibus_t mb;
    MinibusCreate(&mb);
    printf("print_info(int i)\n");
    MinibusDisplay(&mb);

    PublicTransport_t pt;
    PublicTransportCopyCreate(&pt, &(mb.m_superclass));
    MinibusDestroy(&mb);
    return (pt);
}

int MaxFunc(const int *t1, const int *t2)
{
    return ((*t1 > *t2) ? *t1 : *t2);
}

void S_TaxiDisplay(Taxi_t s)
{
    TaxiDisplay(&s);
}
/**************************** PublicTransport *******************************/
void PublicTransportCreat(PublicTransport_t *pt)
{
    pt->vptr = GetVtable(PUBLICTRANSPORT);

    ++PublicTransport_s_count;
    pt->m_license_plate = PublicTransport_s_count;

    printf("PublicTransport::Ctor()%d\n", pt->m_license_plate);

    return;
}

void PublicTransportDestroy(void *pt)
{
    --PublicTransport_s_count;

    printf("PublicTransport::Dtor()%d\n", ((PublicTransport_t *)pt)->m_license_plate);

    return;
}

void PublicTransportCopyCreate(PublicTransport_t *pt, const PublicTransport_t *other)
{
    UNUSED(other);
    pt->vptr = GetVtable(PUBLICTRANSPORT);

    ++PublicTransport_s_count;
    pt->m_license_plate = PublicTransport_s_count;

    printf("PublicTransport::CCtor() %d\n", pt->m_license_plate);
}

void PublicTransportDisplay(void const *pt)
{
    printf("PublicTransport::display(): %d\n", ((PublicTransport_t *)pt)->m_license_plate);
}

int PublicTransportGetID(PublicTransport_t *const pt)
{
    return (pt->m_license_plate);
}

/**************************** Minibus *******************************/

void MinibusCreate(Minibus_t *mb)
{
    PublicTransportCreat(&(mb->m_superclass));

    mb->vptr = GetVtableMB();
    mb->m_numSeats = 20;

    printf("Minibus::Ctor()\n");
    return;
}

void MinibusDestroy(void *mb)
{
    printf("Minibus::Dtor()\n");
    PublicTransportDestroy((void *)&(((Minibus_t *)mb)->m_superclass));
    return;
}

void MinibusDisplay(void const *mb)
{
    printf("Minibus::display() ID:%d", MinibusGetID((Minibus_t *)mb));
    printf(" num seats:%d\n", ((Minibus_t *)mb)->m_numSeats);
}

int MinibusGetID(Minibus_t *const mb)
{
    return (mb->m_superclass.m_license_plate);
}

void Wash(void *obj, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n", minutes, PublicTransportGetID(&((Minibus_t *)obj)->m_superclass));
}

/**************************** Taxi *******************************/

void TaxiCreate(Taxi_t *tx)
{
    PublicTransportCreat(&(tx->m_superclass));
    tx->vptr = GetVtable(TAXI);
    printf("Taxi::Ctor()\n");
    return;
}

void TaxiDestroy(void *tx)
{
    printf("Taxi::Dtor()\n");
    PublicTransportDestroy((void *)&(((Taxi_t *)tx)->m_superclass));
    return;
}

void TaxiDisplay(void const *tx)
{
    printf("Taxi::display() ID:%d\n", TaxiGetID((Taxi_t *)tx));
}

int TaxiGetID(Taxi_t *const tx)
{
    return (tx->m_superclass.m_license_plate);
}

void TaxiCopyCreate(Taxi_t *tx, const Taxi_t *other)
{
    PublicTransportCopyCreate(&tx->m_superclass, &other->m_superclass);
    printf("Taxi::CCtor()\n");
    tx->vptr = GetVtable(TAXI);

    TaxiGetID(tx);
    return;
}

/**************************** SpecialTaxi *******************************/

void SpecialTaxiCreate(SpecialTaxi_t *s_tx)
{
    TaxiCreate(&(s_tx->m_superclass));
    s_tx->vptr = GetVtable(SPECIALTAXI);

    printf("SpecialTaxi::Ctor()\n");
    return;
}

void SpecialTaxiDestroy(void *s_tx)
{
    printf("SpecialTaxi::Dtor()\n");
    TaxiDestroy((void *)&(((SpecialTaxi_t *)s_tx)->m_superclass));
    return;
}

void SpecialTaxiDisplay(void const *s_tx)
{
    printf("SpecialTaxi::display() ID:%d\n", SpecialTaxiGetID((SpecialTaxi_t *)s_tx));
}

int SpecialTaxiGetID(SpecialTaxi_t *const s_tx)
{
    return (s_tx->m_superclass.m_superclass.m_license_plate);
}
/**************************** main *******************************/

int main(int argc, char **argv, char **envp)
{
    UNUSED(argc), UNUSED(argv), UNUSED(envp);

    Minibus_t m;
    MinibusCreate(&m);
    PrintInfoMinibus(&m);

    PublicTransport_t pt = PrintInfoInt(3);
    PublicTransportDisplay(&pt);
    PublicTransportDestroy(&pt);

    PublicTransport_t *array[3] = {NULL};

    array[0] = Init(Allocet((void **)(array), GetSizeof(MINIBUS)), MINIBUS);
    array[1] = Init(Allocet((void **)(array + 1), GetSizeof(TAXI)), TAXI);
    array[2] = Init(Allocet((void **)(array + 2), GetSizeof(MINIBUS)), MINIBUS);

    for (size_t i = 0; i < 3; ++i)
    {
        array[i]->vptr->Display(array[i]);
    }

    for (size_t i = 0; i < 3; ++i)
    {
        array[i]->vptr->Dtor(array[i]);
        free(array[i]);
    }

    Minibus_t temp_mb_1;
    Taxi_t temp_taxi_2;
    PublicTransport_t temp_pt_3;
    PublicTransport_t arr2[3] = {0};

    MinibusCreate(&temp_mb_1);
    PublicTransportCopyCreate((arr2 + 0), &temp_mb_1.m_superclass);
    MinibusDestroy(&temp_mb_1);

    TaxiCreate(&temp_taxi_2);
    PublicTransportCopyCreate((arr2 + 1), &(temp_taxi_2.m_superclass));
    TaxiDestroy(&temp_taxi_2);

    PublicTransportCreat(&temp_pt_3);
    arr2[2] = temp_pt_3;

    for (size_t i = 0; i < 3; ++i)
    {
        arr2[i].vptr->Display(arr2 + i);
    }

    PrintInfoPublicTransport(arr2 + 0);

    PrintCount();

    Minibus_t m2;
    MinibusCreate(&m2);

    PrintCount();

    Minibus_t arr3[4];

    for (int i = 0; i < 4; ++i)
    {
        MinibusCreate(arr3 + i);
    }

    Taxi_t *arr4 = (Taxi_t *)malloc(GetSizeof(TAXI) * 4);
    for (size_t i = 0; i < 4; ++i)
    {
        TaxiCreate(arr4 + i);
    }

    for (size_t i = 0; i < 4; ++i)
    {
        (arr4 + (3 - i))->vptr->Dtor(arr4 + (3 - i));
    }

    free(arr4);
    int i1 = 1;
    int i2 = 2;
    printf("%d\n", MaxFunc(&i1, &i2));

    i2 = 2.0f;
    i1 = 1;
    printf("%d\n", MaxFunc(&i1, &i2));

    SpecialTaxi_t st;
    SpecialTaxiCreate(&st);
    Taxi_t tx1;
    TaxiCopyCreate(&tx1, &st.m_superclass);

    S_TaxiDisplay(tx1);
    TaxiDestroy(&tx1);
    /*PublicConvoy *ts1 = new PublicConvoy();
    PublicConvoy *ts2 = new PublicConvoy(*ts1);
    ts1->display();
    ts2->display();
    delete ts1;
    ts2->display(); // this crashes. fix the bug!
    delete ts2;*/
    /*     printf("------------------------------------------------\n");
 */
    SpecialTaxiDestroy(&st);

    for (int i = 3; i > -1; --i)
    {
        MinibusDestroy(arr3 + i);
    }
    MinibusDestroy(&m2);
    for (int i = 2; i > -1; --i)
    {
        PublicTransportDestroy(&arr2[i]);
    }
    MinibusDestroy(&m);
    return 0;
}
