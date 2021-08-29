#ifndef ILRD_RD102_CPP2C_H
#define ILRD_RD102_CPP2C_H

#include <stddef.h> /* size_t */

#define UNUSED(x) ((void)(x))

typedef struct vtable_mb vtable_mb_t;
typedef struct vtable vtable_t;

typedef struct PublicTransport PublicTransport_t;
typedef struct Minibus Minibus_t;
typedef struct Taxi Taxi_t;
typedef struct SpecialTaxi SpecialTaxi_t;

/******************************* Struct Definition *******************************/

typedef enum type_id
{
    PUBLICTRANSPORT = 0,
    MINIBUS,
    TAXI,
    SPECIALTAXI,
    NUM_OF_TYPE,
} typeid_t;

/******************************* FDecleretions *******************************/
void PublicTransportCreat(PublicTransport_t *pt);
void PublicTransportDestroy(void *pt);
void PublicTransportCopyCreate(PublicTransport_t *pt, const PublicTransport_t *other);
void PublicTransportDisplay(void const *pt);
int PublicTransportGetID(PublicTransport_t *const pt);
void PublicTransportInit(PublicTransport_t **pt);

void MinibusCreate(Minibus_t *mb);
void MinibusDestroy(void *mb);
void MinibusDisplay(void const *mb);
int MinibusGetID(Minibus_t *const mb);
void Wash(void *obj, int minutes);

void TaxiCreate(Taxi_t *tx);
void TaxiCopyCreate(Taxi_t *tx, const Taxi_t *other);
void TaxiDestroy(void *tx);
void TaxiDisplay(void const *tx);
int TaxiGetID(Taxi_t *const tx);

void SpecialTaxiCreate(SpecialTaxi_t *s_tx);
void SpecialTaxiDestroy(void *s_tx);
void SpecialTaxiDisplay(void const *s_tx);
int SpecialTaxiGetID(SpecialTaxi_t *const s_tx);

/**************************** general *******************************/

size_t GetSizeof(typeid_t type);
vtable_t *GetVtable(typeid_t type);

vtable_t *GetVptrPT(PublicTransport_t *pt);
vtable_t *GetVptrMB(Minibus_t *mb);
vtable_t *GetVptrTX(Taxi_t *tx);
vtable_t *GetVptrSTX(SpecialTaxi_t *s_tx);

void *Allocet(void **location, size_t size_of_alloc);
void *Init(void **obj_ptr, typeid_t flag);

void PrintInfoPublicTransport(PublicTransport_t *pt);
void PrintInfoVoid();
void PrintInfoMinibus(Minibus_t *mb);
PublicTransport_t PrintInfoInt(int i);

int MaxFunc(const int *t1, const int *t2);

void S_TaxiDisplay(Taxi_t s);

#endif /* ILRD_RD102_CPP2C_H */
