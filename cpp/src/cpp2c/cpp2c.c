#include <stdio.h>
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "cpp2c.h"

static size_t types_size[NUM_OF_TYPE] = {sizeof(PublicTransport_t), sizeof(Minibus_t), sizeof(Taxi_t), sizeof(SpecialTaxi_t)};

/*-----------v-table----------------------*/

struct vtable
{
    void (*Dtor)(void *);
    void (*Display)(void const *);
    void (*Wash)(void *, int);
    typeid_t typeid;
};

vtable_t g_publictransport_vtble = {PublicTransportDestroy, PublicTransportDisplay, Wash, PUBLICTRANSPORT};
vtable_t g_minibus_vtble = {MinibusDestroy, MinibusDisplay, Wash, MINIBUS};

vtable_t g_taxi_vtble = {TaxiDestroy, TaxiDisplay, Wash, TAXI};
vtable_t g_staxi_vtble = {SpecialTaxiDestroy, SpecialTaxiDisplay, Wash, SPECIALTAXI};

/*-----------static funcs ---------------*/

static int PublicTransport_s_count = 0;

/**************************** allocet *******************************/

void *Allocet(void **obj_ptr, typeid_t flag)
{
    *obj_ptr = malloc(types_size[flag]);

    switch (flag)
    {
    case PUBLICTRANSPORT:
        PublicTransportCreat((*obj_ptr));
        break;
    case MINIBUS:
        MinibusCreate(*obj_ptr);
        break;
    case TAXI:
        TaxiCreate(*obj_ptr);
        break;
    case SPECIALTAXI:
        // PublicTransportCreat(*obj_ptr);
        break;
    default:
        PublicTransportCreat((*obj_ptr));
        break;
    }
    return (*obj_ptr);
}
/**************************** general *******************************/



static void print_count()
{
    printf("s_count: %d\n", PublicTransport_s_count);
}

void print_info_PT(void *obj)
{
    switch (((PublicTransport_t *)obj)->vptr->typeid)
    {
    case PUBLICTRANSPORT:
        PublicTransportDisplay((void *)obj);
        break;
    case MINIBUS:
        PublicTransportDisplay((void *)&(((Minibus_t *)obj)->m_pt));
        break;
    case TAXI:
        TaxiDisplay((void *)&(((Taxi_t *)obj)->m_pt));
        break;
    case SPECIALTAXI:
        SpecialTaxiDisplay((void *)&(((SpecialTaxi_t *)obj)->m_pt));
        break;
    default:
        PublicTransportDisplay((void *)obj);
        break;
    }
}

void print_info_v()
{
    print_count();
}

void print_info_M(Minibus_t *m)
{
    Wash(m, 3);
}

PublicTransport_t print_info_pI(int i)
{
    Minibus_t ret;
    MinibusCreate(&ret);
    printf("print_info(int i)\n");
    MinibusDisplay(&ret);

    PublicTransport_t pt;
    PublicTransportCopyCreate(&pt, &(ret.m_pt));
    MinibusDestroy(&ret);
    return (pt);
}

int max_func(const int *t1, const int *t2)
{
    return ((*t1 > *t2) ? *t1 : *t2);
}

void taxi_display(Taxi_t s)
{
    TaxiDisplay(&s);
}
/**************************** PublicTransport *******************************/
void PublicTransportCreat(PublicTransport_t *pt)
{
    pt->vptr = &g_publictransport_vtble;

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
    pt->vptr = &g_publictransport_vtble;

    ++PublicTransport_s_count;
    pt->m_license_plate = PublicTransport_s_count;

    printf("PublicTransport::CCtor() %d\n", pt->m_license_plate);
}

void PublicTransportDisplay(void const *obj)
{
    printf("PublicTransport::display(): %d\n", ((PublicTransport_t *)obj)->m_license_plate);
}

int PublicTransportGetID(PublicTransport_t *const obj)
{
    return (obj->m_license_plate);
}

/**************************** Minibus *******************************/

void MinibusCreate(Minibus_t *mb)
{
    PublicTransportCreat(&(mb->m_pt));
    mb->vptr = &g_minibus_vtble;
    mb->m_numSeats = 20;

    printf("Minibus::Ctor()\n");
    return;
}

void MinibusDestroy(void *mb)
{
    printf("Minibus::Dtor()\n");
    PublicTransportDestroy((void *)&(((Minibus_t *)mb)->m_pt));
    return;
}

void MinibusDisplay(void const *obj)
{
    printf("Minibus::display() ID:%d", MinibusGetID((Minibus_t *)obj));
    printf(" num seats:%d\n", ((Minibus_t *)obj)->m_numSeats);
}

int MinibusGetID(Minibus_t *const obj)
{
    return (obj->m_pt.m_license_plate);
}

void Wash(void *obj, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n", minutes, PublicTransportGetID(&((Minibus_t *)obj)->m_pt));
}

/**************************** Taxi *******************************/

void TaxiCreate(Taxi_t *tx)
{
    PublicTransportCreat(&(tx->m_pt));
    tx->vptr = &g_taxi_vtble;

    printf("Taxi::Ctor()\n");
    return;
}

void TaxiDestroy(void *tx)
{
    printf("Taxi::Dtor()\n");
    PublicTransportDestroy((void *)&(((Taxi_t *)tx)->m_pt));
    return;
}

void TaxiDisplay(void const *obj)
{
    printf("Taxi::display() ID:%d\n", TaxiGetID((Taxi_t *)obj));
}

int TaxiGetID(Taxi_t *const obj)
{
    return (obj->m_pt.m_license_plate);
}

void TaxiCopyCreate(Taxi_t *tx, const Taxi_t *other)
{
    PublicTransportCopyCreate(&tx->m_pt, &other->m_pt);
    printf("Taxi::CCtor()\n");
    tx->vptr = &g_publictransport_vtble;
    TaxiGetID(tx);
    return;
}

/**************************** SpecialTaxi *******************************/

void SpecialTaxiCreate(SpecialTaxi_t *s_tx)
{
    TaxiCreate(&(s_tx->m_pt));
    s_tx->vptr = &g_staxi_vtble;

    printf("SpecialTaxi::Ctor()\n");
    return;
}

void SpecialTaxiDestroy(void *s_tx)
{
    printf("SpecialTaxi::Dtor()\n");
    TaxiDestroy((void *)&(((SpecialTaxi_t *)s_tx)->m_pt));
    return;
}

void SpecialTaxiDisplay(void const *obj)
{
    printf("SpecialTaxi::display() ID:%d\n", SpecialTaxiGetID((SpecialTaxi_t *)obj));
}

int SpecialTaxiGetID(SpecialTaxi_t *const obj)
{
    return (obj->m_pt.m_pt.m_license_plate);
}
/**************************** main *******************************/

int main(int argc, char **argv, char **envp)
{
    Minibus_t m;
    MinibusCreate(&m);
    print_info_M(&m);

    PublicTransport_t pt = print_info_pI(3);
    PublicTransportDisplay(&pt);
    PublicTransportDestroy(&pt);
    PublicTransport_t *array[] = {
        (PublicTransport_t *)Allocet((void **)array, MINIBUS),
        (PublicTransport_t *)Allocet((void **)(array + 1), TAXI),
        (PublicTransport_t *)Allocet((void **)(array + 2), MINIBUS),
    };

    for (int i = 0; i < 3; ++i)
    {
        array[i]->vptr->Display(array[i]);
    }

    for (int i = 0; i < 3; ++i)
    {
        array[i]->vptr->Dtor(array[i]);
        free(array[i]);
    }

    PublicTransport_t arr2[3] = {0};

    Minibus_t temp_mb_1;
    MinibusCreate(&temp_mb_1);
    PublicTransportCopyCreate((arr2 + 0), &temp_mb_1.m_pt);

    MinibusDestroy(&temp_mb_1);

    Taxi_t temp_taxi_2;
    TaxiCreate(&temp_taxi_2);
    PublicTransportCopyCreate((arr2 + 1), &(temp_taxi_2.m_pt));
    TaxiDestroy(&temp_taxi_2);

    PublicTransport_t temp_pt_3;
    PublicTransportCreat(&temp_pt_3);
    arr2[2] = temp_pt_3;

    for (int i = 0; i < 3; ++i)
    {
        arr2[i].vptr->Display(arr2 + i);
    }

    print_info_PT(arr2 + 0);

    print_count();

    Minibus_t m2;
    MinibusCreate(&m2);

    print_count();

    Minibus_t arr3[4];
    for (int i = 0; i < 4; ++i)
    {
        MinibusCreate(arr3 + i);
    }

    Taxi_t *arr4 = (Taxi_t *)malloc(types_size[TAXI] * 4);
    for (int i = 0; i < 4; ++i)
    {
        TaxiCreate(arr4 + i);
    }

    for (int i = 3; i > -1; --i)
    {
        TaxiDestroy(arr4 + i);
    }

    free(arr4);
    int x1 = 1;
    int x2 = 2;
    printf("%d\n", max_func(&x1, &x2));
    
    int x2 = 2;

    x2 = 2.0f;

    printf("%d\n", max_func(&x1, &x2));

/*     printf("------------------------------------------------\n");
 */
    SpecialTaxi_t st;
    SpecialTaxiCreate(&st);
    Taxi_t tx1;
    TaxiCopyCreate(&tx1, &st.m_pt);

    taxi_display(tx1);
    TaxiDestroy(&tx1);
    /*PublicConvoy *ts1 = new PublicConvoy();
    PublicConvoy *ts2 = new PublicConvoy(*ts1);
    ts1->display();
    ts2->display();
    delete ts1;
    ts2->display(); // this crashes. fix the bug!
    delete ts2;*/
/*     printf("------------------------------------------------\n");
 */    SpecialTaxiDestroy(&st);

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
