#ifndef ILRD_RD102_CPP2C_H
#define ILRD_RD102_CPP2C_H

#include <stddef.h> /* size_t */

#define UNUSED(x) ((void)(x))

typedef struct vtable vtable_t;

typedef struct PublicTransport PublicTransport_t;
typedef struct Minibus Minibus_t;
typedef struct Taxi Taxi_t;
typedef struct SpecialTaxi SpecialTaxi_t;
typedef struct PublicConvoy PublicConvoy_t;

/******************************* Struct Definition *******************************/

typedef enum type_id
{
    PUBLICTRANSPORT = 0,
    MINIBUS,
    TAXI,
    SPECIALTAXI,
    PUBLICCONVOY,
    NUM_OF_TYPE,
} typeid_t;

/******************************* FDecleretions *******************************/
void PublicTransportCreat(PublicTransport_t *pt);
void PublicTransportDestroy(void *pt);
void PublicTransportCopyCreate(PublicTransport_t *pt, const PublicTransport_t *other);
void PublicTransportDisplay(void const *pt);
int GetID(PublicTransport_t *const pt);
void PublicTransportInit(PublicTransport_t **pt);

void MinibusCreate(Minibus_t *mb);
void MinibusCopyCreate(void *mb, const void *other);
void MinibusDestroy(void *mb);
void MinibusDisplay(void const *mb);
void Wash(void *obj, int minutes);

void TaxiCreate(Taxi_t *tx);
void TaxiCopyCreate(void *tx, const void *other);
void TaxiDestroy(void *tx);
void TaxiDisplay(void const *tx);

void SpecialTaxiCreate(SpecialTaxi_t *s_tx);
void SpecialTaxiDestroy(void *s_tx);
void SpecialTaxiDisplay(void const *s_tx);


void PublicConvoyCreate(PublicConvoy_t *pc);
void PublicConvoyCopyCreate(PublicConvoy_t *pc, const PublicConvoy_t *other);
void PublicConvoyDestroy(void *pc);
void PublicConvoyDisplay(void const *pc);

/**************************** general *******************************/

size_t GetSizeof(typeid_t type);
vtable_t *GetVtable(typeid_t type);

void *Allocet(void **location, size_t size_of_alloc);
void *Init(void **obj_ptr, typeid_t flag);

void PrintInfoPublicTransport(PublicTransport_t *pt);
void PrintInfoVoid();
void PrintInfoMinibus(Minibus_t *mb);
PublicTransport_t *PrintInfoIntAndHiden(PublicTransport_t *hiden, int i);

int MaxFunc(const int *t1, const int *t2);

void S_TaxiDisplay(Taxi_t s);

#endif /* ILRD_RD102_CPP2C_H */
