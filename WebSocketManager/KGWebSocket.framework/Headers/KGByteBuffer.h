/**
 * Copyright (c) 2007-2013, Kaazing Corporation. All rights reserved.
 */

#import <Foundation/Foundation.h>


@interface KGByteBuffer : NSObject {
@private
    NSMutableData* _data;
    int _capacity;
    int _limit;
    int _mark;
    int _position;
    int _arrayOffset;
    
@public
    id  peer; // stores peer KCByteArray
}

- (int) remaining;
- (int) position;
- (void) setPosition:(int)position;
- (int) limit;
- (void) setLimit:(int)limit;
- (BOOL) hasRemaining;
- (int) arrayOffset;

+ (KGByteBuffer *) allocate:(int)size;
- (KGByteBuffer *) duplicate;
- (KGByteBuffer *) slice;
- (KGByteBuffer *) compact;
- (void) skip:(int)length;
- (void) mark;
- (void) flip;
- (void) reset;
- (int) indexOf:(char)byte;

- (char) get;
- (char) getAt:(int)index;
- (unsigned short) getUnsignedShort;
- (short) getShort;
//- (unsigned int) getUnsignedInt;
- (int) getInt;
- (int) getIntAt:(int)index;
- (long long) getLong;
- (NSString*) getString;
- (NSString*) getStringWithEncoding:(NSStringEncoding)charset;

- (void) put:(char)value;
- (void) putShort:(short)value;
- (void) putUnsignedShort:(unsigned short)value;
- (void) putUnsignedInt:(unsigned int)value;
- (void) putInt:(int)value;
- (void) putLong:(long long)value;
- (void) putBuffer:(KGByteBuffer *)buffer;
- (void) putString:(NSString*)string;
- (void) putString:(NSString*)string withEncoding:(NSStringEncoding)charset;

// Non-portable Core implementation
- (NSMutableData*) data;
+ (KGByteBuffer *) wrapData:(NSData*)array;
//+ (KGByteBuffer*) wrapData:(NSData*)array offset:(int)offset length:(int)length;
//- (void) getData:(NSData*)data offset:(int)offset length:(int)length;
- (NSData*) getData:(int)size;
- (NSData*) getDataAt:(int)index size:(int)size;
- (void) putData:(NSData*)data;
- (void) putBytes:(uint8_t*)bytes length:(int)length;

// Portable Chai implementation (defined elsewhere)
//- (KCByteArray*) array;
//+ (KGByteBuffer*) wrap:(KCByteArray*)array;
//+ (KGByteBuffer*) wrap:(KCByteArray*)array offset:(int)offset length:(int)length;
//- (void) get:(KCByteArray*)byteArray offset:(int)offset length:(int)length;
//- (KCByteArray*) getBytes:(int)size;
//- (KCByteArray*) getBytesAt:(int)index size:(int)size;
//- (void) putBytes:(KCByteArray*)byteArray;

- (void *) bytesFrom:(int)index;
- (void *) bytesFromPosition;

@end