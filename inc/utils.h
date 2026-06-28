
#define BIT(x) (1UL << (x))
#define BITS(n, x) ((n)UL << (x))

#define SET_BIT(REG, BIT) ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT) ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT) ((REG) & (BIT))
#define MODIFY_REG(REG, MASK, VAL)                                             \
  ((REG) = (((REG) & ~(MASK)) | ((VAL) & (MASK))))

#define PIN(bank, num) (((uint32_t)((bank) - 'A') << 8) | (num))
#define PINNO(pin) (pin & 255)
#define PINBANK(pin) ((pin >> 8) & 0xFF)

enum { HIGH = 1, LOW = 0 };
