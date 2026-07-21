#include "pmm.h"

#define PAGE_SIZE 4096

#define MEMORY_SIZE (128 * 1024 * 1024)
#define TOTAL_PAGES (MEMORY_SIZE / PAGE_SIZE)

static uint8_t bitmap[TOTAL_PAGES / 8];


static void set_page_used(uint32_t page)
{
    bitmap[page / 8] |= (1 << (page % 8));
}


static void set_page_free(uint32_t page)
{
    bitmap[page / 8] &= ~(1 << (page % 8));
}


static int test_page(uint32_t page)
{
    return bitmap[page / 8] & (1 << (page % 8));
}


void pmm_init(void)
{
    
    for(uint32_t i = 0; i < TOTAL_PAGES / 8; i++)
    {
        bitmap[i] = 0;
    }

    
    for(uint32_t i = 0; i < 0x100000 / PAGE_SIZE; i++)
    {
        set_page_used(i);
    }
}


void* pmm_alloc_page(void)
{
    for(uint32_t i = 0; i < TOTAL_PAGES; i++)
    {
        if(!test_page(i))
        {
            set_page_used(i);

            return (void*)(i * PAGE_SIZE);
        }
    }

    return 0;
}


void pmm_free_page(void* page)
{
    uint32_t address = (uint32_t)page;

    uint32_t page_number = address / PAGE_SIZE;

    set_page_free(page_number);
}
