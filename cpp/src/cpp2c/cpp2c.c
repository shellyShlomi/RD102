// Developer: Shelly Shlomi
// Status: Approved
// Reviewer: Yakov .M.
// Group: RD102
// date: 29.8.21
// description: Implementation cpp2c phas 1

// Developer: Shelly Shlomi
// Status: Done
// Reviewer: Maor
// Group: RD102
// date: 9.9.21
// description: Implementation cpp2c phas 2

#include <stdlib.h> /* malloc */
#include <stdio.h>  /*printf*/

#include "cpp2c.h"
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/******************************* Struct Definition *******************************/

struct vtable
{
    void (*Dtor)(void *);
    void (*Display)(void const *);
    void (*Wash)(void *, int);
};

struct PublicTransport
{
    vtable_t *vptr;
    int m_license_plate;
};

struct Minibus
{
    PublicTransport_t m_superclass;
    int m_numSeats;
};

struct Taxi
{
    PublicTransport_t m_superclass;
};

struct SpecialTaxi
{
    Taxi_t m_superclass;
};

struct PublicConvoy
{
    PublicTransport_t m_superclass;

    PublicTransport_t *m_pt1;
    PublicTransport_t *m_pt2;
    Minibus_t m_m;
    Taxi_t m_t;
};

/******************************* Static Data Memb ******************************/

static int PublicTransport_s_count = 0;

/******************************** Static Function ********************************/
static void PrintCount();

size_t GetSizeof(typeid_t type)
{
    static size_t types_size[NUM_OF_TYPE] = {sizeof(PublicTransport_t),
                                             sizeof(Minibus_t),
                                             sizeof(Taxi_t),
                                             sizeof(SpecialTaxi_t),
                                             sizeof(PublicConvoy_t)};
    return (types_size[type]);
}

/******************************** Static V-Table *******************************/

vtable_t *GetVtable(typeid_t type)
{
    static vtable_t g_publictransport_vtble = {PublicTransportDestroy,
                                               PublicTransportDisplay,
                                               NULL};

    static vtable_t g_minibus_vtble = {MinibusDestroy,
                                       MinibusDisplay,
                                       Wash};

    static vtable_t g_taxi_vtble = {TaxiDestroy,
                                    TaxiDisplay, NULL};

    static vtable_t g_staxi_vtble = {SpecialTaxiDestroy,
                                     SpecialTaxiDisplay, NULL};

    static vtable_t g_publicconvoy_vtble = {PublicConvoyDestroy,
                                            PublicConvoyDisplay, NULL};
    vtable_t *return_table = NULL;

    switch (type)
    {
    case PUBLICTRANSPORT:
    {
        return_table = &g_publictransport_vtble;
        break;
    }
    case MINIBUS:
    {
        return_table = &g_minibus_vtble;
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
    case PUBLICCONVOY:
    {
        return_table = &g_publicconvoy_vtble;
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
        MinibusCreate((Minibus_t *)(*obj_ptr));
        break;
    }
    case TAXI:
    {
        TaxiCreate((Taxi_t *)(*obj_ptr));
        break;
    }
    case SPECIALTAXI:
    {
        SpecialTaxiCreate((SpecialTaxi_t *)(*obj_ptr));
        break;
    }
    default:
    {
        PublicTransportCreat((PublicTransport_t *)(*obj_ptr));
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
    ((PublicTransport_t *)mb)->vptr->Wash(mb, 3);
    return;
}

//copy ellision
PublicTransport_t *PrintInfoIntAndHiden(PublicTransport_t *hiden, int i)
{
    UNUSED(i);
    Minibus_t mb;
    MinibusCreate(&mb);
    printf("print_info(int i)\n");
    MinibusDisplay(&mb);

    PublicTransportCopyCreate(hiden, ((PublicTransport_t *)&mb));
    MinibusDestroy(&mb);
    return (hiden);
}

int MaxFunc(const int *t1, const int *t2)
{
    return ((*t1 > *t2) ? *t1 : *t2);
}

void S_TaxiDisplay(Taxi_t s)
{
    TaxiDisplay(&s);
    return;
}
/**************************** PublicTransport *******************************/

void PublicTransportCreat(PublicTransport_t *pt)
{
    ++PublicTransport_s_count;
    pt->m_license_plate = PublicTransport_s_count;
    pt->vptr = GetVtable(PUBLICTRANSPORT);

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
    ++PublicTransport_s_count;
    pt->m_license_plate = PublicTransport_s_count;
    pt->vptr = GetVtable(PUBLICTRANSPORT);

    printf("PublicTransport::CCtor() %d\n", pt->m_license_plate);
    return;
}

void PublicTransportDisplay(void const *pt)
{
    printf("PublicTransport::display(): %d\n", ((PublicTransport_t *)pt)->m_license_plate);
    return;
}

int GetID(PublicTransport_t *const pt)
{
    return (pt->m_license_plate);
}

/**************************** Minibus *******************************/

void MinibusCreate(Minibus_t *mb)
{
    PublicTransportCreat((PublicTransport_t *)mb);

    mb->m_numSeats = 20;
    ((PublicTransport_t *)mb)->vptr = GetVtable(MINIBUS);

    printf("Minibus::Ctor()\n");
    return;
}

void MinibusCopyCreate(Minibus_t *mb, const Minibus_t *other)
{
    PublicTransportCopyCreate(((PublicTransport_t *)mb), ((PublicTransport_t *)other));
    mb->m_numSeats = other->m_numSeats;
    printf("Minibus::CCtor()\n");

    ((PublicTransport_t *)mb)->vptr = GetVtable(MINIBUS);

    return;
}

void MinibusDestroy(void *mb)
{
    printf("Minibus::Dtor()\n");
    PublicTransportDestroy((void *)((PublicTransport_t *)mb));

    return;
}

void MinibusDisplay(void const *mb)
{
    printf("Minibus::display() ID:%d", GetID(((PublicTransport_t *)mb)));
    printf(" num seats:%d\n", ((Minibus_t *)mb)->m_numSeats);
    return;
}

void Wash(void *obj, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n", minutes, GetID(((PublicTransport_t *)obj)));
    return;
}

/**************************** Taxi *******************************/

void TaxiCreate(Taxi_t *tx)
{
    PublicTransportCreat((PublicTransport_t *)tx);
    ((PublicTransport_t *)tx)->vptr = GetVtable(TAXI);

    printf("Taxi::Ctor()\n");
    return;
}

void TaxiCopyCreate(Taxi_t *tx, const Taxi_t *other)
{
    PublicTransportCopyCreate(((PublicTransport_t *)tx), ((PublicTransport_t *)other));
    printf("Taxi::CCtor()\n");

    ((PublicTransport_t *)tx)->vptr = GetVtable(TAXI);

    return;
}

void TaxiDestroy(void *tx)
{
    printf("Taxi::Dtor()\n");
    PublicTransportDestroy((void *)((PublicTransport_t *)tx));
    return;
}

void TaxiDisplay(void const *tx)
{
    printf("Taxi::display() ID:%d\n", GetID((PublicTransport_t *)tx));
    return;
}

/**************************** SpecialTaxi *******************************/

void SpecialTaxiCreate(SpecialTaxi_t *s_tx)
{
    TaxiCreate(((Taxi_t *)s_tx));
    ((PublicTransport_t *)s_tx)->vptr = GetVtable(SPECIALTAXI);

    printf("SpecialTaxi::Ctor()\n");
    return;
}

void SpecialTaxiDestroy(void *s_tx)
{
    printf("SpecialTaxi::Dtor()\n");
    TaxiDestroy((void *)((PublicTransport_t *)s_tx));
    return;
}

void SpecialTaxiDisplay(void const *s_tx)
{
    printf("SpecialTaxi::display() ID:%d\n", GetID(((PublicTransport_t *)s_tx)));
    return;
}
/**************************** PublicConvoy *******************************/

void PublicConvoyCreate(PublicConvoy_t *pc)
{
    PublicTransportCreat((PublicTransport_t *)pc);

    pc->m_pt1 = (PublicTransport_t *)malloc(sizeof(Minibus_t));
    MinibusCreate((Minibus_t *)(pc->m_pt1));

    pc->m_pt2 = (PublicTransport_t *)malloc(sizeof(Taxi_t));
    TaxiCreate((Taxi_t *)(pc->m_pt2));

    MinibusCreate(&(pc->m_m));
    TaxiCreate(&(pc->m_t));
    ((PublicTransport_t *)pc)->vptr = GetVtable(PUBLICCONVOY);

    return;
}

void PublicConvoyCopyCreate(PublicConvoy_t *pc, const PublicConvoy_t *other)
{
    PublicTransportCopyCreate(((PublicTransport_t *)pc), ((PublicTransport_t *)other));

    pc->m_pt1 = (PublicTransport_t *)malloc(sizeof(Minibus_t));
    MinibusCopyCreate((Minibus_t *)(pc->m_pt1), (Minibus_t *)(other->m_pt1));

    pc->m_pt2 = (PublicTransport_t *)malloc(sizeof(Taxi_t));
    TaxiCopyCreate((Taxi_t *)(pc->m_pt2), (Taxi_t *)(other->m_pt2));

    MinibusCopyCreate(&(pc->m_m), &(other->m_m));
    TaxiCopyCreate(&(pc->m_t), &(other->m_t));


    ((PublicTransport_t *)pc)->vptr = GetVtable(PUBLICCONVOY);

    return;
}

void PublicConvoyDestroy(void *pc)
{

    (((PublicConvoy_t *)pc)->m_pt1)->vptr->Dtor(((PublicConvoy_t *)pc)->m_pt1);
    free(((PublicConvoy_t *)pc)->m_pt1);

    (((PublicConvoy_t *)pc)->m_pt2)->vptr->Dtor(((PublicConvoy_t *)pc)->m_pt2);
    free((void *)((PublicConvoy_t *)pc)->m_pt2);

    TaxiDestroy((void *)&(((PublicConvoy_t *)pc)->m_t));
    MinibusDestroy((void *)&(((PublicConvoy_t *)pc)->m_m));

    PublicTransportDestroy((void *)((PublicTransport_t *)pc));

    return;
}

void PublicConvoyDisplay(void const *pc)
{
    ((PublicConvoy_t *)pc)->m_pt1->vptr->Display(((PublicConvoy_t *)pc)->m_pt1);
    ((PublicConvoy_t *)pc)->m_pt2->vptr->Display(((PublicConvoy_t *)pc)->m_pt2);
    MinibusDisplay((void *)&(((PublicConvoy_t *)pc)->m_m));
    TaxiDisplay((void *)&(((PublicConvoy_t *)pc)->m_t));
    return;
}

/**************************** main *******************************/

int main(int argc, char **argv, char **envp)
{
    UNUSED(argc), UNUSED(argv), UNUSED(envp);

    PublicTransport_t hiden;

    Minibus_t m;
    MinibusCreate(&m);
    PrintInfoMinibus(&m);

    PublicTransportDisplay(PrintInfoIntAndHiden(&hiden, 3));
    PublicTransportDestroy(&hiden);

    PublicTransport_t *array[3] = {NULL};
    Allocet((void **)(array), GetSizeof(MINIBUS));
    MinibusCreate((Minibus_t *)*array);
    Allocet((void **)(array + 1), GetSizeof(TAXI));
    TaxiCreate((Taxi_t *)*(array + 1));
    Allocet((void **)(array + 2), GetSizeof(MINIBUS));
    MinibusCreate((Minibus_t *)*(array + 2));

    for (size_t i = 0; i < 3; ++i)
    {
        ((PublicTransport_t *)array[i])->vptr->Display(array[i]);
    }

    for (size_t i = 0; i < 3; ++i)
    {
        ((PublicTransport_t *)array[i])->vptr->Dtor(array[i]);
        free(array[i]);
    }

    Minibus_t temp_mb_1;
    Taxi_t temp_taxi_2;
    PublicTransport_t arr2[3] = {0};

    MinibusCreate(&temp_mb_1);
    PublicTransportCopyCreate((arr2 + 0), &temp_mb_1.m_superclass);
    MinibusDestroy(&temp_mb_1);

    TaxiCreate(&temp_taxi_2);
    PublicTransportCopyCreate((arr2 + 1), &(temp_taxi_2.m_superclass));
    TaxiDestroy(&temp_taxi_2);

    PublicTransportCreat(arr2 + 2);

    for (size_t i = 0; i < 3; ++i)
    {
        ((PublicTransport_t *)(arr2 + i))->vptr->Display(arr2 + i);
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
        ((PublicTransport_t *)(arr4 + (3 - i)))->vptr->Dtor(arr4 + (3 - i));
    }

    free(arr4);
    int i1 = 1;
    int i2 = 2;
    printf("%d\n", MAX(i1, i2));

    i2 = 2.0f;
    i1 = 1;
    printf("%d\n", MaxFunc(&i1, &i2));

    SpecialTaxi_t st;
    SpecialTaxiCreate(&st);
    Taxi_t tx1;
    TaxiCopyCreate(&tx1, &st.m_superclass);

    S_TaxiDisplay(tx1);
    TaxiDestroy(&tx1);

    PublicConvoy_t *ts1 = (PublicConvoy_t *)malloc(sizeof(PublicConvoy_t));
    PublicConvoyCreate(ts1);

    PublicConvoy_t *ts2 = (PublicConvoy_t *)malloc(sizeof(PublicConvoy_t));
    PublicConvoyCopyCreate(ts2, ts1);

    ts1->m_superclass.vptr->Display(ts1);
    ts2->m_superclass.vptr->Display(ts2);

    ts1->m_superclass.vptr->Dtor(ts1);
    free(ts1);

    ts2->m_superclass.vptr->Display(ts2);

    ts2->m_superclass.vptr->Dtor(ts2);
    free(ts2);

    printf("------------------------------------------------\n");
    printf("------------------------------------------------\n");

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
