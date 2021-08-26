#ifndef ILRD_RD102_CPP2C_H
#define ILRD_RD102_CPP2C_H

typedef struct vtable vtable_t;
typedef struct PublicTransport PublicTransport_t;
typedef struct Minibus Minibus_t;

typedef struct Taxi Taxi_t;

typedef struct SpecialTaxi SpecialTaxi_t;

typedef enum type_id
{
    PUBLICTRANSPORT,
    MINIBUS,
    TAXI,
    SPECIALTAXI,
    NUM_OF_TYPE,
} typeid_t;

typedef union types
{
    PublicTransport_t *pt;
    Minibus_t *mb;
    Taxi_t *tx;
    SpecialTaxi_t *s_tx;

} types_t;

struct PublicTransport
{
    vtable_t *vptr;
    void (*PrintCount)(void);
    int m_license_plate;
};

struct Minibus
{
    vtable_t *vptr;
    int m_numSeats;
    PublicTransport_t m_pt;
};

struct Taxi
{
    vtable_t *vptr;
    PublicTransport_t m_pt;
};

struct SpecialTaxi
{
    vtable_t *vptr;
    Taxi_t m_pt;
};

void PublicTransportCreat(PublicTransport_t *pt);
void PublicTransportDestroy(void *pt);
void PublicTransportCopyCreate(PublicTransport_t *pt, const PublicTransport_t *other);
void PublicTransportDisplay(void const *);
int PublicTransportGetID(PublicTransport_t *const);

void Wash(void *obj, int minutes);
void MinibusCreate(Minibus_t *mb);
void MinibusDestroy(void *pt);
void MinibusDisplay(void const *obj);
int MinibusGetID(Minibus_t *const obj);

void TaxiCreate(Taxi_t *tx);
void TaxiDestroy(void *tx);
void TaxiDisplay(void const *obj);
int TaxiGetID(Taxi_t *const obj);


void SpecialTaxiCreate(SpecialTaxi_t *s_tx);
void SpecialTaxiDestroy(void *s_tx);
void SpecialTaxiDisplay(void const *obj);
int SpecialTaxiGetID(SpecialTaxi_t *const obj);

/**************************** general *******************************/

void *Allocet(void **obj_ptr, typeid_t flag);

#endif /* ILRD_RD102_CPP2C_H */
