# Results
2947/2947 (100.00%)

## Summary
| Category                       | Passes   | Fails    |
| ------------------------------ | -------- | -------- |
| Minty                          |        0 |        0 |
| Debug                          |       43 |        0 |
| Base                           |        7 |        0 |
| Compression                    |       10 |        0 |
| Array::Iterator                |       85 |        0 |
| Array::ConstIterator           |       85 |        0 |
| Array::ReverseIterator         |       85 |        0 |
| Array::ConstReverseIterator    |       85 |        0 |
| Array                          |       55 |        0 |
| Color                          |       72 |        0 |
| List::Iterator                 |       85 |        0 |
| List::ConstIterator            |       82 |        0 |
| List::ReverseIterator          |       82 |        0 |
| List::ConstReverseIterator     |       82 |        0 |
| List                           |      258 |        0 |
| Map::Iterator                  |       17 |        0 |
| Map::ConstIterator             |       17 |        0 |
| Map                            |      113 |        0 |
| Pair                           |       54 |        0 |
| Queue                          |       36 |        0 |
| Set::Iterator                  |       15 |        0 |
| Set::ConstIterator             |       15 |        0 |
| Set                            |      105 |        0 |
| Stack                          |       81 |        0 |
| String::Iterator               |       89 |        0 |
| String::ConstIterator          |       89 |        0 |
| String                         |      152 |        0 |
| Vector::Iterator               |       85 |        0 |
| Vector::ConstIterator          |       85 |        0 |
| Vector::ReverseIterator        |       85 |        0 |
| Vector::ConstReverseIterator   |       85 |        0 |
| Vector                         |      292 |        0 |
| File                           |       11 |        0 |
| PhysicalFile                   |       86 |        0 |
| VirtualFile                    |       77 |        0 |
| MemoryManager                  |       87 |        0 |
| MemoryPool                     |       31 |        0 |
| MemoryStack                    |       27 |        0 |
| Wrap                           |       74 |        0 |
| Wrapper                        |       23 |        0 |

## Failures
No failures! :)

# Categories

## Minty
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |

## Debug
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 10: Set Foreground Color (OUTPUT == "\033[30m")                                                                                  |
|  PASS  | 11: Set Foreground Color (OUTPUT == "\033[31m")                                                                                  |
|  PASS  | 12: Set Foreground Color (OUTPUT == "\033[32m")                                                                                  |
|  PASS  | 13: Set Foreground Color (OUTPUT == "\033[33m")                                                                                  |
|  PASS  | 14: Set Foreground Color (OUTPUT == "\033[34m")                                                                                  |
|  PASS  | 15: Set Foreground Color (OUTPUT == "\033[35m")                                                                                  |
|  PASS  | 16: Set Foreground Color (OUTPUT == "\033[36m")                                                                                  |
|  PASS  | 17: Set Foreground Color (OUTPUT == "\033[37m")                                                                                  |
|  PASS  | 18: Set Foreground Color (OUTPUT == "\033[90m")                                                                                  |
|  PASS  | 19: Set Foreground Color (OUTPUT == "\033[91m")                                                                                  |
|  PASS  | 20: Set Foreground Color (OUTPUT == "\033[92m")                                                                                  |
|  PASS  | 21: Set Foreground Color (OUTPUT == "\033[93m")                                                                                  |
|  PASS  | 22: Set Foreground Color (OUTPUT == "\033[94m")                                                                                  |
|  PASS  | 23: Set Foreground Color (OUTPUT == "\033[95m")                                                                                  |
|  PASS  | 24: Set Foreground Color (OUTPUT == "\033[96m")                                                                                  |
|  PASS  | 25: Set Foreground Color (OUTPUT == "\033[97m")                                                                                  |
|  PASS  | 30: Set Background Color (OUTPUT == "\033[40m")                                                                                  |
|  PASS  | 31: Set Background Color (OUTPUT == "\033[41m")                                                                                  |
|  PASS  | 32: Set Background Color (OUTPUT == "\033[42m")                                                                                  |
|  PASS  | 33: Set Background Color (OUTPUT == "\033[43m")                                                                                  |
|  PASS  | 34: Set Background Color (OUTPUT == "\033[44m")                                                                                  |
|  PASS  | 35: Set Background Color (OUTPUT == "\033[45m")                                                                                  |
|  PASS  | 36: Set Background Color (OUTPUT == "\033[46m")                                                                                  |
|  PASS  | 37: Set Background Color (OUTPUT == "\033[47m")                                                                                  |
|  PASS  | 38: Set Background Color (OUTPUT == "\033[100m")                                                                                 |
|  PASS  | 39: Set Background Color (OUTPUT == "\033[101m")                                                                                 |
|  PASS  | 40: Set Background Color (OUTPUT == "\033[102m")                                                                                 |
|  PASS  | 41: Set Background Color (OUTPUT == "\033[103m")                                                                                 |
|  PASS  | 42: Set Background Color (OUTPUT == "\033[104m")                                                                                 |
|  PASS  | 43: Set Background Color (OUTPUT == "\033[105m")                                                                                 |
|  PASS  | 44: Set Background Color (OUTPUT == "\033[106m")                                                                                 |
|  PASS  | 45: Set Background Color (OUTPUT == "\033[107m")                                                                                 |
|  PASS  | 50: Reset (OUTPUT == "\033[0m")                                                                                                  |
|  PASS  | 55: Reset (OUTPUT == "\033[31m\033[0m")                                                                                          |
|  PASS  | 60: Write (OUTPUT == "")                                                                                                         |
|  PASS  | 62: Write (OUTPUT == "Hello, World!")                                                                                            |
|  PASS  | 63: Write (OUTPUT == "Hello, World! 13")                                                                                         |
|  PASS  | 68: Write Line (OUTPUT == "\n")                                                                                                  |
|  PASS  | 70: Write Line (OUTPUT == "Hello, World!\n")                                                                                     |
|  PASS  | 71: Write Line (OUTPUT == "Hello, World! 13\n")                                                                                  |
|  PASS  | 76: Flush (OUTPUT == "")                                                                                                         |
|  PASS  | 83: Flush (file.get_size() == 0)                                                                                                 |
|  PASS  | 88: Flush (file.get_size() > 0)                                                                                                  |

## Base
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 13: Allocate/Deallocate (ptr != nullptr)                                                                                         |
|  PASS  | 20: Construct/Destruct (ptr != nullptr)                                                                                          |
|  PASS  | 21: Construct/Destruct (*ptr == 5)                                                                                               |
|  PASS  | 29: Construct/Destruct Array (ptr != nullptr)                                                                                    |
|  PASS  | 32: Construct/Destruct Array (ptr[i] == 5)                                                                                       |
|  PASS  | 32: Construct/Destruct Array (ptr[i] == 5)                                                                                       |
|  PASS  | 32: Construct/Destruct Array (ptr[i] == 5)                                                                                       |

## Compression
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 28: Compress Bound (compress(buffer, bufferSize, stringData, stringSize))                                                        |
|  PASS  | 29: Compress Bound (bufferSize <= bound)                                                                                         |
|  PASS  | 41: Compress (compress(buffer, bufferSize, stringData, stringSize))                                                              |
|  PASS  | 42: Compress (compress(nullptr, bufferSize, stringData, stringSize))                                                             |
|  PASS  | 43: Compress (compress(buffer, bufferSize, nullptr, stringSize))                                                                 |
|  PASS  | 55: Uncompress (compress(buffer, bufferSize, stringData, stringSize))                                                            |
|  PASS  | 62: Uncompress (uncompress(buffer2, bufferSize2, buffer, bufferSize))                                                            |
|  PASS  | 63: Uncompress (uncompress(nullptr, bufferSize2, buffer, bufferSize))                                                            |
|  PASS  | 64: Uncompress (uncompress(buffer2, bufferSize2, nullptr, bufferSize))                                                           |
|  PASS  | 69: Uncompress (text == text2)                                                                                                   |

## Array::Iterator
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 13: Copy Constructor (*copy == 5)                                                                                                |
|  PASS  | 14: Copy Constructor (*(copy + 1) == 5)                                                                                          |
|  PASS  | 15: Copy Constructor (*(copy + 2) == 5)                                                                                          |
|  PASS  | 16: Copy Constructor (copy + 3 == test.end())                                                                                    |
|  PASS  | 17: Copy Constructor (*++copy == 5)                                                                                              |
|  PASS  | 18: Copy Constructor (*++copy == 5)                                                                                              |
|  PASS  | 19: Copy Constructor (++copy == test.end())                                                                                      |
|  PASS  | 21: Copy Constructor (*copy++ == 5)                                                                                              |
|  PASS  | 22: Copy Constructor (*copy++ == 5)                                                                                              |
|  PASS  | 23: Copy Constructor (*copy++ == 5)                                                                                              |
|  PASS  | 24: Copy Constructor (copy == test.end())                                                                                        |
|  PASS  | 32: Move Constructor (*copy == 5)                                                                                                |
|  PASS  | 33: Move Constructor (*(copy + 1) == 5)                                                                                          |
|  PASS  | 34: Move Constructor (*(copy + 2) == 5)                                                                                          |
|  PASS  | 35: Move Constructor (copy + 3 == test.end())                                                                                    |
|  PASS  | 36: Move Constructor (*++copy == 5)                                                                                              |
|  PASS  | 37: Move Constructor (*++copy == 5)                                                                                              |
|  PASS  | 38: Move Constructor (++copy == test.end())                                                                                      |
|  PASS  | 41: Move Constructor (*copy++ == 5)                                                                                              |
|  PASS  | 42: Move Constructor (*copy++ == 5)                                                                                              |
|  PASS  | 43: Move Constructor (*copy++ == 5)                                                                                              |
|  PASS  | 44: Move Constructor (copy == test.end())                                                                                        |
|  PASS  | 52: Copy Operator (*copy == 5)                                                                                                   |
|  PASS  | 53: Copy Operator (*(copy + 1) == 5)                                                                                             |
|  PASS  | 54: Copy Operator (*(copy + 2) == 5)                                                                                             |
|  PASS  | 55: Copy Operator (copy + 3 == test.end())                                                                                       |
|  PASS  | 56: Copy Operator (*++copy == 5)                                                                                                 |
|  PASS  | 57: Copy Operator (*++copy == 5)                                                                                                 |
|  PASS  | 58: Copy Operator (++copy == test.end())                                                                                         |
|  PASS  | 60: Copy Operator (*copy++ == 5)                                                                                                 |
|  PASS  | 61: Copy Operator (*copy++ == 5)                                                                                                 |
|  PASS  | 62: Copy Operator (*copy++ == 5)                                                                                                 |
|  PASS  | 63: Copy Operator (copy == test.end())                                                                                           |
|  PASS  | 71: Move Operator (*copy == 5)                                                                                                   |
|  PASS  | 72: Move Operator (*(copy + 1) == 5)                                                                                             |
|  PASS  | 73: Move Operator (*(copy + 2) == 5)                                                                                             |
|  PASS  | 74: Move Operator (copy + 3 == test.end())                                                                                       |
|  PASS  | 75: Move Operator (*++copy == 5)                                                                                                 |
|  PASS  | 76: Move Operator (*++copy == 5)                                                                                                 |
|  PASS  | 77: Move Operator (++copy == test.end())                                                                                         |
|  PASS  | 80: Move Operator (*copy++ == 5)                                                                                                 |
|  PASS  | 81: Move Operator (*copy++ == 5)                                                                                                 |
|  PASS  | 82: Move Operator (*copy++ == 5)                                                                                                 |
|  PASS  | 83: Move Operator (copy == test.end())                                                                                           |
|  PASS  | 90: Dereference Operator (*it == 5)                                                                                              |
|  PASS  | 91: Dereference Operator (*(it + 1) == 5)                                                                                        |
|  PASS  | 92: Dereference Operator (*(it + 2) == 5)                                                                                        |
|  PASS  | 99: Increment Operator (*it == 5)                                                                                                |
|  PASS  | 100: Increment Operator (*(it + 1) == 5)                                                                                         |
|  PASS  | 101: Increment Operator (*(it + 2) == 5)                                                                                         |
|  PASS  | 102: Increment Operator (it + 3 == test.end())                                                                                   |
|  PASS  | 103: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 104: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 105: Increment Operator (++it == test.end())                                                                                     |
|  PASS  | 107: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 108: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 109: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 110: Increment Operator (it == test.end())                                                                                       |
|  PASS  | 117: Decrement Operator (*(it - 1) == 5)                                                                                         |
|  PASS  | 118: Decrement Operator (*(it - 2) == 5)                                                                                         |
|  PASS  | 119: Decrement Operator (it - 3 == test.begin())                                                                                 |
|  PASS  | 120: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 121: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 122: Decrement Operator (--it == test.begin())                                                                                   |
|  PASS  | 125: Decrement Operator (*it-- == 5)                                                                                             |
|  PASS  | 126: Decrement Operator (*it-- == 5)                                                                                             |
|  PASS  | 127: Decrement Operator (it == test.begin())                                                                                     |
|  PASS  | 134: Addition Operator (*it == 5)                                                                                                |
|  PASS  | 135: Addition Operator (*(it + 1) == 5)                                                                                          |
|  PASS  | 136: Addition Operator (*(it + 2) == 5)                                                                                          |
|  PASS  | 143: Subtraction Operator (it - 3 == test.begin())                                                                               |
|  PASS  | 144: Subtraction Operator (it - 2 == test.begin() + 1)                                                                           |
|  PASS  | 145: Subtraction Operator (it - 1 == test.begin() + 2)                                                                           |
|  PASS  | 153: Equal Operator (it == copy)                                                                                                 |
|  PASS  | 154: Equal Operator (copy == it)                                                                                                 |
|  PASS  | 155: Equal Operator (it == test.begin())                                                                                         |
|  PASS  | 156: Equal Operator (test.begin() == it)                                                                                         |
|  PASS  | 157: Equal Operator (copy == test.begin())                                                                                       |
|  PASS  | 158: Equal Operator (test.begin() == copy)                                                                                       |
|  PASS  | 166: Not Equal Operator (!(it != copy))                                                                                          |
|  PASS  | 167: Not Equal Operator (!(copy != it))                                                                                          |
|  PASS  | 168: Not Equal Operator (!(it != test.begin()))                                                                                  |
|  PASS  | 169: Not Equal Operator (!(test.begin() != it))                                                                                  |
|  PASS  | 170: Not Equal Operator (!(copy != test.begin()))                                                                                |
|  PASS  | 171: Not Equal Operator (!(test.begin() != copy))                                                                                |

## Array::ConstIterator
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 182: Copy Constructor (*copy == 5)                                                                                               |
|  PASS  | 183: Copy Constructor (*(copy + 1) == 5)                                                                                         |
|  PASS  | 184: Copy Constructor (*(copy + 2) == 5)                                                                                         |
|  PASS  | 185: Copy Constructor (copy + 3 == test.end())                                                                                   |
|  PASS  | 186: Copy Constructor (*++copy == 5)                                                                                             |
|  PASS  | 187: Copy Constructor (*++copy == 5)                                                                                             |
|  PASS  | 188: Copy Constructor (++copy == test.end())                                                                                     |
|  PASS  | 190: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 191: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 192: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 193: Copy Constructor (copy == test.end())                                                                                       |
|  PASS  | 201: Move Constructor (*copy == 5)                                                                                               |
|  PASS  | 202: Move Constructor (*(copy + 1) == 5)                                                                                         |
|  PASS  | 203: Move Constructor (*(copy + 2) == 5)                                                                                         |
|  PASS  | 204: Move Constructor (copy + 3 == test.end())                                                                                   |
|  PASS  | 205: Move Constructor (*++copy == 5)                                                                                             |
|  PASS  | 206: Move Constructor (*++copy == 5)                                                                                             |
|  PASS  | 207: Move Constructor (++copy == test.end())                                                                                     |
|  PASS  | 210: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 211: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 212: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 213: Move Constructor (copy == test.end())                                                                                       |
|  PASS  | 221: Copy Operator (*copy == 5)                                                                                                  |
|  PASS  | 222: Copy Operator (*(copy + 1) == 5)                                                                                            |
|  PASS  | 223: Copy Operator (*(copy + 2) == 5)                                                                                            |
|  PASS  | 224: Copy Operator (copy + 3 == test.end())                                                                                      |
|  PASS  | 225: Copy Operator (*++copy == 5)                                                                                                |
|  PASS  | 226: Copy Operator (*++copy == 5)                                                                                                |
|  PASS  | 227: Copy Operator (++copy == test.end())                                                                                        |
|  PASS  | 229: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 230: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 231: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 232: Copy Operator (copy == test.end())                                                                                          |
|  PASS  | 240: Move Operator (*copy == 5)                                                                                                  |
|  PASS  | 241: Move Operator (*(copy + 1) == 5)                                                                                            |
|  PASS  | 242: Move Operator (*(copy + 2) == 5)                                                                                            |
|  PASS  | 243: Move Operator (copy + 3 == test.end())                                                                                      |
|  PASS  | 244: Move Operator (*++copy == 5)                                                                                                |
|  PASS  | 245: Move Operator (*++copy == 5)                                                                                                |
|  PASS  | 246: Move Operator (++copy == test.end())                                                                                        |
|  PASS  | 249: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 250: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 251: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 252: Move Operator (copy == test.end())                                                                                          |
|  PASS  | 259: Dereference Operator (*it == 5)                                                                                             |
|  PASS  | 260: Dereference Operator (*(it + 1) == 5)                                                                                       |
|  PASS  | 261: Dereference Operator (*(it + 2) == 5)                                                                                       |
|  PASS  | 268: Increment Operator (*it == 5)                                                                                               |
|  PASS  | 269: Increment Operator (*(it + 1) == 5)                                                                                         |
|  PASS  | 270: Increment Operator (*(it + 2) == 5)                                                                                         |
|  PASS  | 271: Increment Operator (it + 3 == test.end())                                                                                   |
|  PASS  | 272: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 273: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 274: Increment Operator (++it == test.end())                                                                                     |
|  PASS  | 276: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 277: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 278: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 279: Increment Operator (it == test.end())                                                                                       |
|  PASS  | 286: Decrement Operator (*(it - 1) == 5)                                                                                         |
|  PASS  | 287: Decrement Operator (*(it - 2) == 5)                                                                                         |
|  PASS  | 288: Decrement Operator (it - 3 == test.begin())                                                                                 |
|  PASS  | 289: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 290: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 291: Decrement Operator (--it == test.begin())                                                                                   |
|  PASS  | 294: Decrement Operator (*it-- == 5)                                                                                             |
|  PASS  | 295: Decrement Operator (*it-- == 5)                                                                                             |
|  PASS  | 296: Decrement Operator (it == test.begin())                                                                                     |
|  PASS  | 303: Addition Operator (*it == 5)                                                                                                |
|  PASS  | 304: Addition Operator (*(it + 1) == 5)                                                                                          |
|  PASS  | 305: Addition Operator (*(it + 2) == 5)                                                                                          |
|  PASS  | 312: Subtraction Operator (it - 3 == test.begin())                                                                               |
|  PASS  | 313: Subtraction Operator (it - 2 == test.begin() + 1)                                                                           |
|  PASS  | 314: Subtraction Operator (it - 1 == test.begin() + 2)                                                                           |
|  PASS  | 322: Equal Operator (it == copy)                                                                                                 |
|  PASS  | 323: Equal Operator (copy == it)                                                                                                 |
|  PASS  | 324: Equal Operator (it == test.begin())                                                                                         |
|  PASS  | 325: Equal Operator (test.begin() == it)                                                                                         |
|  PASS  | 326: Equal Operator (copy == test.begin())                                                                                       |
|  PASS  | 327: Equal Operator (test.begin() == copy)                                                                                       |
|  PASS  | 335: Not Equal Operator (!(it != copy))                                                                                          |
|  PASS  | 336: Not Equal Operator (!(copy != it))                                                                                          |
|  PASS  | 337: Not Equal Operator (!(it != test.begin()))                                                                                  |
|  PASS  | 338: Not Equal Operator (!(test.begin() != it))                                                                                  |
|  PASS  | 339: Not Equal Operator (!(copy != test.begin()))                                                                                |
|  PASS  | 340: Not Equal Operator (!(test.begin() != copy))                                                                                |

## Array::ReverseIterator
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 351: Copy Constructor (*copy == 5)                                                                                               |
|  PASS  | 352: Copy Constructor (*(copy + 1) == 5)                                                                                         |
|  PASS  | 353: Copy Constructor (*(copy + 2) == 5)                                                                                         |
|  PASS  | 354: Copy Constructor (copy + 3 == test.rend())                                                                                  |
|  PASS  | 355: Copy Constructor (*++copy == 5)                                                                                             |
|  PASS  | 356: Copy Constructor (*++copy == 5)                                                                                             |
|  PASS  | 357: Copy Constructor (++copy == test.rend())                                                                                    |
|  PASS  | 359: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 360: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 361: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 362: Copy Constructor (copy == test.rend())                                                                                      |
|  PASS  | 370: Move Constructor (*copy == 5)                                                                                               |
|  PASS  | 371: Move Constructor (*(copy + 1) == 5)                                                                                         |
|  PASS  | 372: Move Constructor (*(copy + 2) == 5)                                                                                         |
|  PASS  | 373: Move Constructor (copy + 3 == test.rend())                                                                                  |
|  PASS  | 374: Move Constructor (*++copy == 5)                                                                                             |
|  PASS  | 375: Move Constructor (*++copy == 5)                                                                                             |
|  PASS  | 376: Move Constructor (++copy == test.rend())                                                                                    |
|  PASS  | 379: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 380: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 381: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 382: Move Constructor (copy == test.rend())                                                                                      |
|  PASS  | 390: Copy Operator (*copy == 5)                                                                                                  |
|  PASS  | 391: Copy Operator (*(copy + 1) == 5)                                                                                            |
|  PASS  | 392: Copy Operator (*(copy + 2) == 5)                                                                                            |
|  PASS  | 393: Copy Operator (copy + 3 == test.rend())                                                                                     |
|  PASS  | 394: Copy Operator (*++copy == 5)                                                                                                |
|  PASS  | 395: Copy Operator (*++copy == 5)                                                                                                |
|  PASS  | 396: Copy Operator (++copy == test.rend())                                                                                       |
|  PASS  | 398: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 399: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 400: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 401: Copy Operator (copy == test.rend())                                                                                         |
|  PASS  | 409: Move Operator (*copy == 5)                                                                                                  |
|  PASS  | 410: Move Operator (*(copy + 1) == 5)                                                                                            |
|  PASS  | 411: Move Operator (*(copy + 2) == 5)                                                                                            |
|  PASS  | 412: Move Operator (copy + 3 == test.rend())                                                                                     |
|  PASS  | 413: Move Operator (*++copy == 5)                                                                                                |
|  PASS  | 414: Move Operator (*++copy == 5)                                                                                                |
|  PASS  | 415: Move Operator (++copy == test.rend())                                                                                       |
|  PASS  | 418: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 419: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 420: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 421: Move Operator (copy == test.rend())                                                                                         |
|  PASS  | 428: Dereference Operator (*it == 5)                                                                                             |
|  PASS  | 429: Dereference Operator (*(it + 1) == 5)                                                                                       |
|  PASS  | 430: Dereference Operator (*(it + 2) == 5)                                                                                       |
|  PASS  | 437: Increment Operator (*it == 5)                                                                                               |
|  PASS  | 438: Increment Operator (*(it + 1) == 5)                                                                                         |
|  PASS  | 439: Increment Operator (*(it + 2) == 5)                                                                                         |
|  PASS  | 440: Increment Operator (it + 3 == test.rend())                                                                                  |
|  PASS  | 441: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 442: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 443: Increment Operator (++it == test.rend())                                                                                    |
|  PASS  | 445: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 446: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 447: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 448: Increment Operator (it == test.rend())                                                                                      |
|  PASS  | 455: Decrement Operator (*(it - 1) == 5)                                                                                         |
|  PASS  | 456: Decrement Operator (*(it - 2) == 5)                                                                                         |
|  PASS  | 457: Decrement Operator (it - 3 == test.rbegin())                                                                                |
|  PASS  | 458: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 459: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 460: Decrement Operator (--it == test.rbegin())                                                                                  |
|  PASS  | 463: Decrement Operator (*it-- == 5)                                                                                             |
|  PASS  | 464: Decrement Operator (*it-- == 5)                                                                                             |
|  PASS  | 465: Decrement Operator (it == test.rbegin())                                                                                    |
|  PASS  | 472: Addition Operator (*it == 5)                                                                                                |
|  PASS  | 473: Addition Operator (*(it + 1) == 5)                                                                                          |
|  PASS  | 474: Addition Operator (*(it + 2) == 5)                                                                                          |
|  PASS  | 481: Subtraction Operator (it - 3 == test.rbegin())                                                                              |
|  PASS  | 482: Subtraction Operator (it - 2 == test.rbegin() + 1)                                                                          |
|  PASS  | 483: Subtraction Operator (it - 1 == test.rbegin() + 2)                                                                          |
|  PASS  | 491: Equal Operator (it == copy)                                                                                                 |
|  PASS  | 492: Equal Operator (copy == it)                                                                                                 |
|  PASS  | 493: Equal Operator (it == test.rbegin())                                                                                        |
|  PASS  | 494: Equal Operator (test.rbegin() == it)                                                                                        |
|  PASS  | 495: Equal Operator (copy == test.rbegin())                                                                                      |
|  PASS  | 496: Equal Operator (test.rbegin() == copy)                                                                                      |
|  PASS  | 504: Not Equal Operator (!(it != copy))                                                                                          |
|  PASS  | 505: Not Equal Operator (!(copy != it))                                                                                          |
|  PASS  | 506: Not Equal Operator (!(it != test.rbegin()))                                                                                 |
|  PASS  | 507: Not Equal Operator (!(test.rbegin() != it))                                                                                 |
|  PASS  | 508: Not Equal Operator (!(copy != test.rbegin()))                                                                               |
|  PASS  | 509: Not Equal Operator (!(test.rbegin() != copy))                                                                               |

## Array::ConstReverseIterator
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 520: Copy Constructor (*copy == 5)                                                                                               |
|  PASS  | 521: Copy Constructor (*(copy + 1) == 5)                                                                                         |
|  PASS  | 522: Copy Constructor (*(copy + 2) == 5)                                                                                         |
|  PASS  | 523: Copy Constructor (copy + 3 == test.rend())                                                                                  |
|  PASS  | 524: Copy Constructor (*++copy == 5)                                                                                             |
|  PASS  | 525: Copy Constructor (*++copy == 5)                                                                                             |
|  PASS  | 526: Copy Constructor (++copy == test.rend())                                                                                    |
|  PASS  | 528: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 529: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 530: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 531: Copy Constructor (copy == test.rend())                                                                                      |
|  PASS  | 539: Move Constructor (*copy == 5)                                                                                               |
|  PASS  | 540: Move Constructor (*(copy + 1) == 5)                                                                                         |
|  PASS  | 541: Move Constructor (*(copy + 2) == 5)                                                                                         |
|  PASS  | 542: Move Constructor (copy + 3 == test.rend())                                                                                  |
|  PASS  | 543: Move Constructor (*++copy == 5)                                                                                             |
|  PASS  | 544: Move Constructor (*++copy == 5)                                                                                             |
|  PASS  | 545: Move Constructor (++copy == test.rend())                                                                                    |
|  PASS  | 548: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 549: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 550: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 551: Move Constructor (copy == test.rend())                                                                                      |
|  PASS  | 559: Copy Operator (*copy == 5)                                                                                                  |
|  PASS  | 560: Copy Operator (*(copy + 1) == 5)                                                                                            |
|  PASS  | 561: Copy Operator (*(copy + 2) == 5)                                                                                            |
|  PASS  | 562: Copy Operator (copy + 3 == test.rend())                                                                                     |
|  PASS  | 563: Copy Operator (*++copy == 5)                                                                                                |
|  PASS  | 564: Copy Operator (*++copy == 5)                                                                                                |
|  PASS  | 565: Copy Operator (++copy == test.rend())                                                                                       |
|  PASS  | 567: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 568: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 569: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 570: Copy Operator (copy == test.rend())                                                                                         |
|  PASS  | 578: Move Operator (*copy == 5)                                                                                                  |
|  PASS  | 579: Move Operator (*(copy + 1) == 5)                                                                                            |
|  PASS  | 580: Move Operator (*(copy + 2) == 5)                                                                                            |
|  PASS  | 581: Move Operator (copy + 3 == test.rend())                                                                                     |
|  PASS  | 582: Move Operator (*++copy == 5)                                                                                                |
|  PASS  | 583: Move Operator (*++copy == 5)                                                                                                |
|  PASS  | 584: Move Operator (++copy == test.rend())                                                                                       |
|  PASS  | 587: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 588: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 589: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 590: Move Operator (copy == test.rend())                                                                                         |
|  PASS  | 597: Dereference Operator (*it == 5)                                                                                             |
|  PASS  | 598: Dereference Operator (*(it + 1) == 5)                                                                                       |
|  PASS  | 599: Dereference Operator (*(it + 2) == 5)                                                                                       |
|  PASS  | 606: Increment Operator (*it == 5)                                                                                               |
|  PASS  | 607: Increment Operator (*(it + 1) == 5)                                                                                         |
|  PASS  | 608: Increment Operator (*(it + 2) == 5)                                                                                         |
|  PASS  | 609: Increment Operator (it + 3 == test.rend())                                                                                  |
|  PASS  | 610: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 611: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 612: Increment Operator (++it == test.rend())                                                                                    |
|  PASS  | 614: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 615: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 616: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 617: Increment Operator (it == test.rend())                                                                                      |
|  PASS  | 624: Decrement Operator (*(it - 1) == 5)                                                                                         |
|  PASS  | 625: Decrement Operator (*(it - 2) == 5)                                                                                         |
|  PASS  | 626: Decrement Operator (it - 3 == test.rbegin())                                                                                |
|  PASS  | 627: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 628: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 629: Decrement Operator (--it == test.rbegin())                                                                                  |
|  PASS  | 632: Decrement Operator (*it-- == 5)                                                                                             |
|  PASS  | 633: Decrement Operator (*it-- == 5)                                                                                             |
|  PASS  | 634: Decrement Operator (it == test.rbegin())                                                                                    |
|  PASS  | 641: Addition Operator (*it == 5)                                                                                                |
|  PASS  | 642: Addition Operator (*(it + 1) == 5)                                                                                          |
|  PASS  | 643: Addition Operator (*(it + 2) == 5)                                                                                          |
|  PASS  | 650: Subtraction Operator (it - 3 == test.rbegin())                                                                              |
|  PASS  | 651: Subtraction Operator (it - 2 == test.rbegin() + 1)                                                                          |
|  PASS  | 652: Subtraction Operator (it - 1 == test.rbegin() + 2)                                                                          |
|  PASS  | 660: Equal Operator (it == copy)                                                                                                 |
|  PASS  | 661: Equal Operator (copy == it)                                                                                                 |
|  PASS  | 662: Equal Operator (it == test.rbegin())                                                                                        |
|  PASS  | 663: Equal Operator (test.rbegin() == it)                                                                                        |
|  PASS  | 664: Equal Operator (copy == test.rbegin())                                                                                      |
|  PASS  | 665: Equal Operator (test.rbegin() == copy)                                                                                      |
|  PASS  | 673: Not Equal Operator (!(it != copy))                                                                                          |
|  PASS  | 674: Not Equal Operator (!(copy != it))                                                                                          |
|  PASS  | 675: Not Equal Operator (!(it != test.rbegin()))                                                                                 |
|  PASS  | 676: Not Equal Operator (!(test.rbegin() != it))                                                                                 |
|  PASS  | 677: Not Equal Operator (!(copy != test.rbegin()))                                                                               |
|  PASS  | 678: Not Equal Operator (!(test.rbegin() != copy))                                                                               |

## Array
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 687: Default Constructor (test.get_size() == 3)                                                                                  |
|  PASS  | 693: Value Constructor (test.get_size() == 3)                                                                                    |
|  PASS  | 694: Value Constructor (test.at(0) == 5)                                                                                         |
|  PASS  | 695: Value Constructor (test.at(1) == 5)                                                                                         |
|  PASS  | 696: Value Constructor (test.at(2) == 5)                                                                                         |
|  PASS  | 702: Initializer List Constructor (test.get_size() == 3)                                                                         |
|  PASS  | 703: Initializer List Constructor (test.at(0) == 0)                                                                              |
|  PASS  | 704: Initializer List Constructor (test.at(1) == 1)                                                                              |
|  PASS  | 705: Initializer List Constructor (test.at(2) == 2)                                                                              |
|  PASS  | 712: Copy Constructor (copy.get_size() == 3)                                                                                     |
|  PASS  | 713: Copy Constructor (copy.at(0) == 5)                                                                                          |
|  PASS  | 714: Copy Constructor (copy.at(1) == 5)                                                                                          |
|  PASS  | 715: Copy Constructor (copy.at(2) == 5)                                                                                          |
|  PASS  | 722: Move Constructor (copy.get_size() == 3)                                                                                     |
|  PASS  | 723: Move Constructor (copy.at(0) == 5)                                                                                          |
|  PASS  | 724: Move Constructor (copy.at(1) == 5)                                                                                          |
|  PASS  | 725: Move Constructor (copy.at(2) == 5)                                                                                          |
|  PASS  | 732: Copy Operator (copy.get_size() == 3)                                                                                        |
|  PASS  | 733: Copy Operator (copy.at(0) == 5)                                                                                             |
|  PASS  | 734: Copy Operator (copy.at(1) == 5)                                                                                             |
|  PASS  | 735: Copy Operator (copy.at(2) == 5)                                                                                             |
|  PASS  | 742: Move Operator (copy.get_size() == 3)                                                                                        |
|  PASS  | 743: Move Operator (copy.at(0) == 5)                                                                                             |
|  PASS  | 744: Move Operator (copy.at(1) == 5)                                                                                             |
|  PASS  | 745: Move Operator (copy.at(2) == 5)                                                                                             |
|  PASS  | 751: Index Operator (test[0] == 5)                                                                                               |
|  PASS  | 752: Index Operator (test[1] == 5)                                                                                               |
|  PASS  | 753: Index Operator (test[2] == 5)                                                                                               |
|  PASS  | 754: Index Operator (test[3])                                                                                                    |
|  PASS  | 760: Const Index Operator (test[0] == 5)                                                                                         |
|  PASS  | 761: Const Index Operator (test[1] == 5)                                                                                         |
|  PASS  | 762: Const Index Operator (test[2] == 5)                                                                                         |
|  PASS  | 763: Const Index Operator (test[3])                                                                                              |
|  PASS  | 769: Get Size (test.get_size() == 3)                                                                                             |
|  PASS  | 775: Get Data (test.get_data() != nullptr)                                                                                       |
|  PASS  | 781: At (test.at(0) == 5)                                                                                                        |
|  PASS  | 782: At (test.at(1) == 5)                                                                                                        |
|  PASS  | 783: At (test.at(2) == 5)                                                                                                        |
|  PASS  | 784: At (test.at(3))                                                                                                             |
|  PASS  | 790: Const At (test.at(0) == 5)                                                                                                  |
|  PASS  | 791: Const At (test.at(1) == 5)                                                                                                  |
|  PASS  | 792: Const At (test.at(2) == 5)                                                                                                  |
|  PASS  | 793: Const At (test.at(3))                                                                                                       |
|  PASS  | 800: Sub (sub.get_size() == 2)                                                                                                   |
|  PASS  | 801: Sub (sub.at(0) == 5)                                                                                                        |
|  PASS  | 802: Sub (sub.at(1) == 5)                                                                                                        |
|  PASS  | 803: Sub (sub.at(2) == 5)                                                                                                        |
|  PASS  | 809: Find (test.find(0) == test.begin())                                                                                         |
|  PASS  | 810: Find (test.find(1) == test.begin() + 1)                                                                                     |
|  PASS  | 811: Find (test.find(2) == test.begin() + 2)                                                                                     |
|  PASS  | 812: Find (test.find(3) == test.end())                                                                                           |
|  PASS  | 818: Const Find (test.find(0) == test.begin())                                                                                   |
|  PASS  | 819: Const Find (test.find(1) == test.begin() + 1)                                                                               |
|  PASS  | 820: Const Find (test.find(2) == test.begin() + 2)                                                                               |
|  PASS  | 821: Const Find (test.find(3) == test.end())                                                                                     |

## Color
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 11: RGBA Channel_t Constructor (color.r == 255)                                                                                  |
|  PASS  | 12: RGBA Channel_t Constructor (color.g == 127)                                                                                  |
|  PASS  | 13: RGBA Channel_t Constructor (color.b == 63)                                                                                   |
|  PASS  | 14: RGBA Channel_t Constructor (color.a == 0)                                                                                    |
|  PASS  | 16: RGBA Channel_t Constructor (color2.r == 0)                                                                                   |
|  PASS  | 17: RGBA Channel_t Constructor (color2.g == 0)                                                                                   |
|  PASS  | 18: RGBA Channel_t Constructor (color2.b == 0)                                                                                   |
|  PASS  | 19: RGBA Channel_t Constructor (color2.a == 255)                                                                                 |
|  PASS  | 25: RGBA Int Constructor (color.r == 255)                                                                                        |
|  PASS  | 26: RGBA Int Constructor (color.g == 127)                                                                                        |
|  PASS  | 27: RGBA Int Constructor (color.b == 63)                                                                                         |
|  PASS  | 28: RGBA Int Constructor (color.a == 0)                                                                                          |
|  PASS  | 30: RGBA Int Constructor (color2.r == 0)                                                                                         |
|  PASS  | 31: RGBA Int Constructor (color2.g == 0)                                                                                         |
|  PASS  | 32: RGBA Int Constructor (color2.b == 0)                                                                                         |
|  PASS  | 33: RGBA Int Constructor (color2.a == 255)                                                                                       |
|  PASS  | 35: RGBA Int Constructor (Color color3(Color::MAX_CHANNEL + 1, 0, 0))                                                            |
|  PASS  | 36: RGBA Int Constructor (Color color4(0, Color::MAX_CHANNEL + 1, 0))                                                            |
|  PASS  | 37: RGBA Int Constructor (Color color5(0, 0, Color::MAX_CHANNEL + 1))                                                            |
|  PASS  | 38: RGBA Int Constructor (Color color6(0, 0, 0, Color::MAX_CHANNEL + 1))                                                         |
|  PASS  | 39: RGBA Int Constructor (Color color7(Color::MIN_CHANNEL - 1, 0, 0))                                                            |
|  PASS  | 40: RGBA Int Constructor (Color color8(0, Color::MIN_CHANNEL - 1, 0))                                                            |
|  PASS  | 41: RGBA Int Constructor (Color color9(0, 0, Color::MIN_CHANNEL - 1))                                                            |
|  PASS  | 42: RGBA Int Constructor (Color color10(0, 0, 0, Color::MIN_CHANNEL - 1))                                                        |
|  PASS  | 48: RGBA Float Constructor (color.r == 255)                                                                                      |
|  PASS  | 49: RGBA Float Constructor (color.g == 127)                                                                                      |
|  PASS  | 50: RGBA Float Constructor (color.b == 63)                                                                                       |
|  PASS  | 51: RGBA Float Constructor (color.a == 0)                                                                                        |
|  PASS  | 53: RGBA Float Constructor (color2.r == 0)                                                                                       |
|  PASS  | 54: RGBA Float Constructor (color2.g == 0)                                                                                       |
|  PASS  | 55: RGBA Float Constructor (color2.b == 0)                                                                                       |
|  PASS  | 56: RGBA Float Constructor (color2.a == 255)                                                                                     |
|  PASS  | 58: RGBA Float Constructor (Color color3(1.1f, 0.0f, 0.0f))                                                                      |
|  PASS  | 59: RGBA Float Constructor (Color color4(0.0f, 1.1f, 0.0f))                                                                      |
|  PASS  | 60: RGBA Float Constructor (Color color5(0.0f, 0.0f, 1.1f))                                                                      |
|  PASS  | 61: RGBA Float Constructor (Color color6(0.0f, 0.0f, 0.0f, 1.1f))                                                                |
|  PASS  | 62: RGBA Float Constructor (Color color7(-0.1f, 0.0f, 0.0f))                                                                     |
|  PASS  | 63: RGBA Float Constructor (Color color8(0.0f, -0.1f, 0.0f))                                                                     |
|  PASS  | 64: RGBA Float Constructor (Color color9(0.0f, 0.0f, -0.1f))                                                                     |
|  PASS  | 65: RGBA Float Constructor (Color color10(0.0f, 0.0f, 0.0f, -0.1f))                                                              |
|  PASS  | 71: Value Constructor (color.r == 255)                                                                                           |
|  PASS  | 72: Value Constructor (color.g == 127)                                                                                           |
|  PASS  | 73: Value Constructor (color.b == 63)                                                                                            |
|  PASS  | 74: Value Constructor (color.a == 0)                                                                                             |
|  PASS  | 76: Value Constructor (color2.r == 0)                                                                                            |
|  PASS  | 77: Value Constructor (color2.g == 0)                                                                                            |
|  PASS  | 78: Value Constructor (color2.b == 0)                                                                                            |
|  PASS  | 79: Value Constructor (color2.a == 255)                                                                                          |
|  PASS  | 86: Equal Operator (color == color2)                                                                                             |
|  PASS  | 87: Equal Operator (color2 == color)                                                                                             |
|  PASS  | 89: Equal Operator (!(color == color3))                                                                                          |
|  PASS  | 90: Equal Operator (!(color3 == color))                                                                                          |
|  PASS  | 97: Not Equal Operator (!(color != color2))                                                                                      |
|  PASS  | 98: Not Equal Operator (!(color2 != color))                                                                                      |
|  PASS  | 100: Not Equal Operator (color != color3)                                                                                        |
|  PASS  | 101: Not Equal Operator (color3 != color)                                                                                        |
|  PASS  | 108: Less Than Operator (!(color < color2))                                                                                      |
|  PASS  | 109: Less Than Operator (!(color2 < color))                                                                                      |
|  PASS  | 111: Less Than Operator (color3 < color)                                                                                         |
|  PASS  | 112: Less Than Operator (!(color < color3))                                                                                      |
|  PASS  | 119: Less Than Or Equal Operator (color <= color2)                                                                               |
|  PASS  | 120: Less Than Or Equal Operator (color2 <= color)                                                                               |
|  PASS  | 122: Less Than Or Equal Operator (color3 <= color)                                                                               |
|  PASS  | 123: Less Than Or Equal Operator (!(color <= color3))                                                                            |
|  PASS  | 130: Greater Than Operator (!(color > color2))                                                                                   |
|  PASS  | 131: Greater Than Operator (!(color2 > color))                                                                                   |
|  PASS  | 133: Greater Than Operator (color > color3)                                                                                      |
|  PASS  | 134: Greater Than Operator (!(color3 > color))                                                                                   |
|  PASS  | 141: Greater Than Or Equal Operator (color >= color2)                                                                            |
|  PASS  | 142: Greater Than Or Equal Operator (color2 >= color)                                                                            |
|  PASS  | 144: Greater Than Or Equal Operator (color >= color3)                                                                            |
|  PASS  | 145: Greater Than Or Equal Operator (!(color3 >= color))                                                                         |

## List::Iterator
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 13: Copy Constructor (*copy == 5)                                                                                                |
|  PASS  | 14: Copy Constructor (*(copy + 1) == 5)                                                                                          |
|  PASS  | 15: Copy Constructor (*(copy + 2) == 5)                                                                                          |
|  PASS  | 16: Copy Constructor (copy + 3 == test.end())                                                                                    |
|  PASS  | 17: Copy Constructor (*++copy == 5)                                                                                              |
|  PASS  | 18: Copy Constructor (*++copy == 5)                                                                                              |
|  PASS  | 19: Copy Constructor (++copy == test.end())                                                                                      |
|  PASS  | 21: Copy Constructor (*copy++ == 5)                                                                                              |
|  PASS  | 22: Copy Constructor (*copy++ == 5)                                                                                              |
|  PASS  | 23: Copy Constructor (*copy++ == 5)                                                                                              |
|  PASS  | 24: Copy Constructor (copy == test.end())                                                                                        |
|  PASS  | 32: Move Constructor (*copy == 5)                                                                                                |
|  PASS  | 33: Move Constructor (*(copy + 1) == 5)                                                                                          |
|  PASS  | 34: Move Constructor (*(copy + 2) == 5)                                                                                          |
|  PASS  | 35: Move Constructor (copy + 3 == test.end())                                                                                    |
|  PASS  | 36: Move Constructor (*++copy == 5)                                                                                              |
|  PASS  | 37: Move Constructor (*++copy == 5)                                                                                              |
|  PASS  | 38: Move Constructor (++copy == test.end())                                                                                      |
|  PASS  | 41: Move Constructor (*copy++ == 5)                                                                                              |
|  PASS  | 42: Move Constructor (*copy++ == 5)                                                                                              |
|  PASS  | 43: Move Constructor (*copy++ == 5)                                                                                              |
|  PASS  | 44: Move Constructor (copy == test.end())                                                                                        |
|  PASS  | 52: Copy Operator (*copy == 5)                                                                                                   |
|  PASS  | 53: Copy Operator (*(copy + 1) == 5)                                                                                             |
|  PASS  | 54: Copy Operator (*(copy + 2) == 5)                                                                                             |
|  PASS  | 55: Copy Operator (copy + 3 == test.end())                                                                                       |
|  PASS  | 56: Copy Operator (*++copy == 5)                                                                                                 |
|  PASS  | 57: Copy Operator (*++copy == 5)                                                                                                 |
|  PASS  | 58: Copy Operator (++copy == test.end())                                                                                         |
|  PASS  | 60: Copy Operator (*copy++ == 5)                                                                                                 |
|  PASS  | 61: Copy Operator (*copy++ == 5)                                                                                                 |
|  PASS  | 62: Copy Operator (*copy++ == 5)                                                                                                 |
|  PASS  | 63: Copy Operator (copy == test.end())                                                                                           |
|  PASS  | 71: Move Operator (*copy == 5)                                                                                                   |
|  PASS  | 72: Move Operator (*(copy + 1) == 5)                                                                                             |
|  PASS  | 73: Move Operator (*(copy + 2) == 5)                                                                                             |
|  PASS  | 74: Move Operator (copy + 3 == test.end())                                                                                       |
|  PASS  | 75: Move Operator (*++copy == 5)                                                                                                 |
|  PASS  | 76: Move Operator (*++copy == 5)                                                                                                 |
|  PASS  | 77: Move Operator (++copy == test.end())                                                                                         |
|  PASS  | 80: Move Operator (*copy++ == 5)                                                                                                 |
|  PASS  | 81: Move Operator (*copy++ == 5)                                                                                                 |
|  PASS  | 82: Move Operator (*copy++ == 5)                                                                                                 |
|  PASS  | 83: Move Operator (copy == test.end())                                                                                           |
|  PASS  | 90: Dereference Operator (*it == 5)                                                                                              |
|  PASS  | 91: Dereference Operator (*(it + 1) == 5)                                                                                        |
|  PASS  | 92: Dereference Operator (*(it + 2) == 5)                                                                                        |
|  PASS  | 99: Increment Operator (*it == 5)                                                                                                |
|  PASS  | 100: Increment Operator (*(it + 1) == 5)                                                                                         |
|  PASS  | 101: Increment Operator (*(it + 2) == 5)                                                                                         |
|  PASS  | 102: Increment Operator (it + 3 == test.end())                                                                                   |
|  PASS  | 103: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 104: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 105: Increment Operator (++it == test.end())                                                                                     |
|  PASS  | 107: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 108: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 109: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 110: Increment Operator (it == test.end())                                                                                       |
|  PASS  | 117: Decrement Operator (*(it - 1) == 5)                                                                                         |
|  PASS  | 118: Decrement Operator (*(it - 2) == 5)                                                                                         |
|  PASS  | 119: Decrement Operator (it - 2 == test.begin())                                                                                 |
|  PASS  | 120: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 121: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 122: Decrement Operator (it == test.begin())                                                                                     |
|  PASS  | 125: Decrement Operator (*it-- == 5)                                                                                             |
|  PASS  | 126: Decrement Operator (*it == 5)                                                                                               |
|  PASS  | 127: Decrement Operator (it == test.begin())                                                                                     |
|  PASS  | 134: Addition Operator (*it == 5)                                                                                                |
|  PASS  | 135: Addition Operator (*(it + 1) == 5)                                                                                          |
|  PASS  | 136: Addition Operator (*(it + 2) == 5)                                                                                          |
|  PASS  | 143: Subtraction Operator (it - 2 == test.begin())                                                                               |
|  PASS  | 144: Subtraction Operator (it - 1 == test.begin() + 1)                                                                           |
|  PASS  | 145: Subtraction Operator (it - 0 == test.begin() + 2)                                                                           |
|  PASS  | 153: Equal Operator (it == copy)                                                                                                 |
|  PASS  | 154: Equal Operator (copy == it)                                                                                                 |
|  PASS  | 155: Equal Operator (it == test.begin())                                                                                         |
|  PASS  | 156: Equal Operator (test.begin() == it)                                                                                         |
|  PASS  | 157: Equal Operator (copy == test.begin())                                                                                       |
|  PASS  | 158: Equal Operator (test.begin() == copy)                                                                                       |
|  PASS  | 166: Not Equal Operator (!(it != copy))                                                                                          |
|  PASS  | 167: Not Equal Operator (!(copy != it))                                                                                          |
|  PASS  | 168: Not Equal Operator (!(it != test.begin()))                                                                                  |
|  PASS  | 169: Not Equal Operator (!(test.begin() != it))                                                                                  |
|  PASS  | 170: Not Equal Operator (!(copy != test.begin()))                                                                                |
|  PASS  | 171: Not Equal Operator (!(test.begin() != copy))                                                                                |

## List::ConstIterator
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 182: Copy Constructor (*copy == 5)                                                                                               |
|  PASS  | 183: Copy Constructor (*(copy + 1) == 5)                                                                                         |
|  PASS  | 184: Copy Constructor (*(copy + 2) == 5)                                                                                         |
|  PASS  | 185: Copy Constructor (copy + 3 == test.end())                                                                                   |
|  PASS  | 186: Copy Constructor (*++copy == 5)                                                                                             |
|  PASS  | 187: Copy Constructor (*++copy == 5)                                                                                             |
|  PASS  | 188: Copy Constructor (++copy == test.end())                                                                                     |
|  PASS  | 190: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 191: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 192: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 193: Copy Constructor (copy == test.end())                                                                                       |
|  PASS  | 201: Move Constructor (*copy == 5)                                                                                               |
|  PASS  | 202: Move Constructor (*(copy + 1) == 5)                                                                                         |
|  PASS  | 203: Move Constructor (*(copy + 2) == 5)                                                                                         |
|  PASS  | 204: Move Constructor (copy + 3 == test.end())                                                                                   |
|  PASS  | 205: Move Constructor (*++copy == 5)                                                                                             |
|  PASS  | 206: Move Constructor (*++copy == 5)                                                                                             |
|  PASS  | 207: Move Constructor (++copy == test.end())                                                                                     |
|  PASS  | 210: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 211: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 212: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 213: Move Constructor (copy == test.end())                                                                                       |
|  PASS  | 221: Copy Operator (*copy == 5)                                                                                                  |
|  PASS  | 222: Copy Operator (*(copy + 1) == 5)                                                                                            |
|  PASS  | 223: Copy Operator (*(copy + 2) == 5)                                                                                            |
|  PASS  | 224: Copy Operator (copy + 3 == test.end())                                                                                      |
|  PASS  | 225: Copy Operator (*++copy == 5)                                                                                                |
|  PASS  | 226: Copy Operator (*++copy == 5)                                                                                                |
|  PASS  | 227: Copy Operator (++copy == test.end())                                                                                        |
|  PASS  | 229: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 230: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 231: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 232: Copy Operator (copy == test.end())                                                                                          |
|  PASS  | 240: Move Operator (*copy == 5)                                                                                                  |
|  PASS  | 241: Move Operator (*(copy + 1) == 5)                                                                                            |
|  PASS  | 242: Move Operator (*(copy + 2) == 5)                                                                                            |
|  PASS  | 243: Move Operator (copy + 3 == test.end())                                                                                      |
|  PASS  | 244: Move Operator (*++copy == 5)                                                                                                |
|  PASS  | 245: Move Operator (*++copy == 5)                                                                                                |
|  PASS  | 246: Move Operator (++copy == test.end())                                                                                        |
|  PASS  | 249: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 250: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 251: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 252: Move Operator (copy == test.end())                                                                                          |
|  PASS  | 259: Dereference Operator (*it == 5)                                                                                             |
|  PASS  | 260: Dereference Operator (*(it + 1) == 5)                                                                                       |
|  PASS  | 261: Dereference Operator (*(it + 2) == 5)                                                                                       |
|  PASS  | 268: Increment Operator (*it == 5)                                                                                               |
|  PASS  | 269: Increment Operator (*(it + 1) == 5)                                                                                         |
|  PASS  | 270: Increment Operator (*(it + 2) == 5)                                                                                         |
|  PASS  | 271: Increment Operator (it + 3 == test.end())                                                                                   |
|  PASS  | 272: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 273: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 274: Increment Operator (++it == test.end())                                                                                     |
|  PASS  | 276: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 277: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 278: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 279: Increment Operator (it == test.end())                                                                                       |
|  PASS  | 286: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 287: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 288: Decrement Operator (it == test.begin())                                                                                     |
|  PASS  | 291: Decrement Operator (*it-- == 5)                                                                                             |
|  PASS  | 292: Decrement Operator (*it == 5)                                                                                               |
|  PASS  | 293: Decrement Operator (it == test.begin())                                                                                     |
|  PASS  | 300: Addition Operator (*it == 5)                                                                                                |
|  PASS  | 301: Addition Operator (*(it + 1) == 5)                                                                                          |
|  PASS  | 302: Addition Operator (*(it + 2) == 5)                                                                                          |
|  PASS  | 309: Subtraction Operator (it - 2 == test.begin())                                                                               |
|  PASS  | 310: Subtraction Operator (it - 1 == test.begin() + 1)                                                                           |
|  PASS  | 311: Subtraction Operator (it - 0 == test.begin() + 2)                                                                           |
|  PASS  | 319: Equal Operator (it == copy)                                                                                                 |
|  PASS  | 320: Equal Operator (copy == it)                                                                                                 |
|  PASS  | 321: Equal Operator (it == test.begin())                                                                                         |
|  PASS  | 322: Equal Operator (test.begin() == it)                                                                                         |
|  PASS  | 323: Equal Operator (copy == test.begin())                                                                                       |
|  PASS  | 324: Equal Operator (test.begin() == copy)                                                                                       |
|  PASS  | 332: Not Equal Operator (!(it != copy))                                                                                          |
|  PASS  | 333: Not Equal Operator (!(copy != it))                                                                                          |
|  PASS  | 334: Not Equal Operator (!(it != test.begin()))                                                                                  |
|  PASS  | 335: Not Equal Operator (!(test.begin() != it))                                                                                  |
|  PASS  | 336: Not Equal Operator (!(copy != test.begin()))                                                                                |
|  PASS  | 337: Not Equal Operator (!(test.begin() != copy))                                                                                |

## List::ReverseIterator
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 348: Copy Constructor (*copy == 5)                                                                                               |
|  PASS  | 349: Copy Constructor (*(copy + 1) == 5)                                                                                         |
|  PASS  | 350: Copy Constructor (*(copy + 2) == 5)                                                                                         |
|  PASS  | 351: Copy Constructor (copy + 3 == test.rend())                                                                                  |
|  PASS  | 352: Copy Constructor (*++copy == 5)                                                                                             |
|  PASS  | 353: Copy Constructor (*++copy == 5)                                                                                             |
|  PASS  | 354: Copy Constructor (++copy == test.rend())                                                                                    |
|  PASS  | 356: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 357: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 358: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 359: Copy Constructor (copy == test.rend())                                                                                      |
|  PASS  | 367: Move Constructor (*copy == 5)                                                                                               |
|  PASS  | 368: Move Constructor (*(copy + 1) == 5)                                                                                         |
|  PASS  | 369: Move Constructor (*(copy + 2) == 5)                                                                                         |
|  PASS  | 370: Move Constructor (copy + 3 == test.rend())                                                                                  |
|  PASS  | 371: Move Constructor (*++copy == 5)                                                                                             |
|  PASS  | 372: Move Constructor (*++copy == 5)                                                                                             |
|  PASS  | 373: Move Constructor (++copy == test.rend())                                                                                    |
|  PASS  | 376: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 377: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 378: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 379: Move Constructor (copy == test.rend())                                                                                      |
|  PASS  | 387: Copy Operator (*copy == 5)                                                                                                  |
|  PASS  | 388: Copy Operator (*(copy + 1) == 5)                                                                                            |
|  PASS  | 389: Copy Operator (*(copy + 2) == 5)                                                                                            |
|  PASS  | 390: Copy Operator (copy + 3 == test.rend())                                                                                     |
|  PASS  | 391: Copy Operator (*++copy == 5)                                                                                                |
|  PASS  | 392: Copy Operator (*++copy == 5)                                                                                                |
|  PASS  | 393: Copy Operator (++copy == test.rend())                                                                                       |
|  PASS  | 395: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 396: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 397: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 398: Copy Operator (copy == test.rend())                                                                                         |
|  PASS  | 406: Move Operator (*copy == 5)                                                                                                  |
|  PASS  | 407: Move Operator (*(copy + 1) == 5)                                                                                            |
|  PASS  | 408: Move Operator (*(copy + 2) == 5)                                                                                            |
|  PASS  | 409: Move Operator (copy + 3 == test.rend())                                                                                     |
|  PASS  | 410: Move Operator (*++copy == 5)                                                                                                |
|  PASS  | 411: Move Operator (*++copy == 5)                                                                                                |
|  PASS  | 412: Move Operator (++copy == test.rend())                                                                                       |
|  PASS  | 415: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 416: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 417: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 418: Move Operator (copy == test.rend())                                                                                         |
|  PASS  | 425: Dereference Operator (*it == 5)                                                                                             |
|  PASS  | 426: Dereference Operator (*(it + 1) == 5)                                                                                       |
|  PASS  | 427: Dereference Operator (*(it + 2) == 5)                                                                                       |
|  PASS  | 434: Increment Operator (*it == 5)                                                                                               |
|  PASS  | 435: Increment Operator (*(it + 1) == 5)                                                                                         |
|  PASS  | 436: Increment Operator (*(it + 2) == 5)                                                                                         |
|  PASS  | 437: Increment Operator (it + 3 == test.rend())                                                                                  |
|  PASS  | 438: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 439: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 440: Increment Operator (++it == test.rend())                                                                                    |
|  PASS  | 442: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 443: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 444: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 445: Increment Operator (it == test.rend())                                                                                      |
|  PASS  | 452: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 453: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 454: Decrement Operator (it == test.rbegin())                                                                                    |
|  PASS  | 457: Decrement Operator (*it-- == 5)                                                                                             |
|  PASS  | 458: Decrement Operator (*it == 5)                                                                                               |
|  PASS  | 459: Decrement Operator (it == test.rbegin())                                                                                    |
|  PASS  | 466: Addition Operator (*it == 5)                                                                                                |
|  PASS  | 467: Addition Operator (*(it + 1) == 5)                                                                                          |
|  PASS  | 468: Addition Operator (*(it + 2) == 5)                                                                                          |
|  PASS  | 475: Subtraction Operator (it - 2 == test.rbegin())                                                                              |
|  PASS  | 476: Subtraction Operator (it - 1 == test.rbegin() + 1)                                                                          |
|  PASS  | 477: Subtraction Operator (it - 0 == test.rbegin() + 2)                                                                          |
|  PASS  | 485: Equal Operator (it == copy)                                                                                                 |
|  PASS  | 486: Equal Operator (copy == it)                                                                                                 |
|  PASS  | 487: Equal Operator (it == test.rbegin())                                                                                        |
|  PASS  | 488: Equal Operator (test.rbegin() == it)                                                                                        |
|  PASS  | 489: Equal Operator (copy == test.rbegin())                                                                                      |
|  PASS  | 490: Equal Operator (test.rbegin() == copy)                                                                                      |
|  PASS  | 498: Not Equal Operator (!(it != copy))                                                                                          |
|  PASS  | 499: Not Equal Operator (!(copy != it))                                                                                          |
|  PASS  | 500: Not Equal Operator (!(it != test.rbegin()))                                                                                 |
|  PASS  | 501: Not Equal Operator (!(test.rbegin() != it))                                                                                 |
|  PASS  | 502: Not Equal Operator (!(copy != test.rbegin()))                                                                               |
|  PASS  | 503: Not Equal Operator (!(test.rbegin() != copy))                                                                               |

## List::ConstReverseIterator
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 514: Copy Constructor (*copy == 5)                                                                                               |
|  PASS  | 515: Copy Constructor (*(copy + 1) == 5)                                                                                         |
|  PASS  | 516: Copy Constructor (*(copy + 2) == 5)                                                                                         |
|  PASS  | 517: Copy Constructor (copy + 3 == test.rend())                                                                                  |
|  PASS  | 518: Copy Constructor (*++copy == 5)                                                                                             |
|  PASS  | 519: Copy Constructor (*++copy == 5)                                                                                             |
|  PASS  | 520: Copy Constructor (++copy == test.rend())                                                                                    |
|  PASS  | 522: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 523: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 524: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 525: Copy Constructor (copy == test.rend())                                                                                      |
|  PASS  | 533: Move Constructor (*copy == 5)                                                                                               |
|  PASS  | 534: Move Constructor (*(copy + 1) == 5)                                                                                         |
|  PASS  | 535: Move Constructor (*(copy + 2) == 5)                                                                                         |
|  PASS  | 536: Move Constructor (copy + 3 == test.rend())                                                                                  |
|  PASS  | 537: Move Constructor (*++copy == 5)                                                                                             |
|  PASS  | 538: Move Constructor (*++copy == 5)                                                                                             |
|  PASS  | 539: Move Constructor (++copy == test.rend())                                                                                    |
|  PASS  | 542: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 543: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 544: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 545: Move Constructor (copy == test.rend())                                                                                      |
|  PASS  | 553: Copy Operator (*copy == 5)                                                                                                  |
|  PASS  | 554: Copy Operator (*(copy + 1) == 5)                                                                                            |
|  PASS  | 555: Copy Operator (*(copy + 2) == 5)                                                                                            |
|  PASS  | 556: Copy Operator (copy + 3 == test.rend())                                                                                     |
|  PASS  | 557: Copy Operator (*++copy == 5)                                                                                                |
|  PASS  | 558: Copy Operator (*++copy == 5)                                                                                                |
|  PASS  | 559: Copy Operator (++copy == test.rend())                                                                                       |
|  PASS  | 561: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 562: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 563: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 564: Copy Operator (copy == test.rend())                                                                                         |
|  PASS  | 572: Move Operator (*copy == 5)                                                                                                  |
|  PASS  | 573: Move Operator (*(copy + 1) == 5)                                                                                            |
|  PASS  | 574: Move Operator (*(copy + 2) == 5)                                                                                            |
|  PASS  | 575: Move Operator (copy + 3 == test.rend())                                                                                     |
|  PASS  | 576: Move Operator (*++copy == 5)                                                                                                |
|  PASS  | 577: Move Operator (*++copy == 5)                                                                                                |
|  PASS  | 578: Move Operator (++copy == test.rend())                                                                                       |
|  PASS  | 581: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 582: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 583: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 584: Move Operator (copy == test.rend())                                                                                         |
|  PASS  | 591: Dereference Operator (*it == 5)                                                                                             |
|  PASS  | 592: Dereference Operator (*(it + 1) == 5)                                                                                       |
|  PASS  | 593: Dereference Operator (*(it + 2) == 5)                                                                                       |
|  PASS  | 600: Increment Operator (*it == 5)                                                                                               |
|  PASS  | 601: Increment Operator (*(it + 1) == 5)                                                                                         |
|  PASS  | 602: Increment Operator (*(it + 2) == 5)                                                                                         |
|  PASS  | 603: Increment Operator (it + 3 == test.rend())                                                                                  |
|  PASS  | 604: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 605: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 606: Increment Operator (++it == test.rend())                                                                                    |
|  PASS  | 608: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 609: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 610: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 611: Increment Operator (it == test.rend())                                                                                      |
|  PASS  | 618: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 619: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 620: Decrement Operator (it == test.rbegin())                                                                                    |
|  PASS  | 623: Decrement Operator (*it-- == 5)                                                                                             |
|  PASS  | 624: Decrement Operator (*it == 5)                                                                                               |
|  PASS  | 625: Decrement Operator (it == test.rbegin())                                                                                    |
|  PASS  | 632: Addition Operator (*it == 5)                                                                                                |
|  PASS  | 633: Addition Operator (*(it + 1) == 5)                                                                                          |
|  PASS  | 634: Addition Operator (*(it + 2) == 5)                                                                                          |
|  PASS  | 641: Subtraction Operator (it - 2 == test.rbegin())                                                                              |
|  PASS  | 642: Subtraction Operator (it - 1 == test.rbegin() + 1)                                                                          |
|  PASS  | 643: Subtraction Operator (it - 0 == test.rbegin() + 2)                                                                          |
|  PASS  | 651: Equal Operator (it == copy)                                                                                                 |
|  PASS  | 652: Equal Operator (copy == it)                                                                                                 |
|  PASS  | 653: Equal Operator (it == test.rbegin())                                                                                        |
|  PASS  | 654: Equal Operator (test.rbegin() == it)                                                                                        |
|  PASS  | 655: Equal Operator (copy == test.rbegin())                                                                                      |
|  PASS  | 656: Equal Operator (test.rbegin() == copy)                                                                                      |
|  PASS  | 664: Not Equal Operator (!(it != copy))                                                                                          |
|  PASS  | 665: Not Equal Operator (!(copy != it))                                                                                          |
|  PASS  | 666: Not Equal Operator (!(it != test.rbegin()))                                                                                 |
|  PASS  | 667: Not Equal Operator (!(test.rbegin() != it))                                                                                 |
|  PASS  | 668: Not Equal Operator (!(copy != test.rbegin()))                                                                               |
|  PASS  | 669: Not Equal Operator (!(test.rbegin() != copy))                                                                               |

## List
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 678: Default Constructor (test.get_size() == 0)                                                                                  |
|  PASS  | 684: Value Constructor (test.get_size() == 10)                                                                                   |
|  PASS  | 687: Value Constructor (test[i] == 5)                                                                                            |
|  PASS  | 687: Value Constructor (test[i] == 5)                                                                                            |
|  PASS  | 687: Value Constructor (test[i] == 5)                                                                                            |
|  PASS  | 687: Value Constructor (test[i] == 5)                                                                                            |
|  PASS  | 687: Value Constructor (test[i] == 5)                                                                                            |
|  PASS  | 687: Value Constructor (test[i] == 5)                                                                                            |
|  PASS  | 687: Value Constructor (test[i] == 5)                                                                                            |
|  PASS  | 687: Value Constructor (test[i] == 5)                                                                                            |
|  PASS  | 687: Value Constructor (test[i] == 5)                                                                                            |
|  PASS  | 687: Value Constructor (test[i] == 5)                                                                                            |
|  PASS  | 691: Value Constructor (test2.get_size() == 0)                                                                                   |
|  PASS  | 697: Initializer List Constructor (test.get_size() == 5)                                                                         |
|  PASS  | 700: Initializer List Constructor (test[i] == i)                                                                                 |
|  PASS  | 700: Initializer List Constructor (test[i] == i)                                                                                 |
|  PASS  | 700: Initializer List Constructor (test[i] == i)                                                                                 |
|  PASS  | 700: Initializer List Constructor (test[i] == i)                                                                                 |
|  PASS  | 700: Initializer List Constructor (test[i] == i)                                                                                 |
|  PASS  | 704: Initializer List Constructor (test2.get_size() == 0)                                                                        |
|  PASS  | 711: Copy Constructor (copy.get_size() == 5)                                                                                     |
|  PASS  | 714: Copy Constructor (copy[i] == i)                                                                                             |
|  PASS  | 714: Copy Constructor (copy[i] == i)                                                                                             |
|  PASS  | 714: Copy Constructor (copy[i] == i)                                                                                             |
|  PASS  | 714: Copy Constructor (copy[i] == i)                                                                                             |
|  PASS  | 714: Copy Constructor (copy[i] == i)                                                                                             |
|  PASS  | 722: Move Constructor (copy.get_size() == 5)                                                                                     |
|  PASS  | 725: Move Constructor (copy[i] == i)                                                                                             |
|  PASS  | 725: Move Constructor (copy[i] == i)                                                                                             |
|  PASS  | 725: Move Constructor (copy[i] == i)                                                                                             |
|  PASS  | 725: Move Constructor (copy[i] == i)                                                                                             |
|  PASS  | 725: Move Constructor (copy[i] == i)                                                                                             |
|  PASS  | 733: Copy Operator (copy.get_size() == 5)                                                                                        |
|  PASS  | 736: Copy Operator (copy[i] == i)                                                                                                |
|  PASS  | 736: Copy Operator (copy[i] == i)                                                                                                |
|  PASS  | 736: Copy Operator (copy[i] == i)                                                                                                |
|  PASS  | 736: Copy Operator (copy[i] == i)                                                                                                |
|  PASS  | 736: Copy Operator (copy[i] == i)                                                                                                |
|  PASS  | 744: Move Operator (copy.get_size() == 5)                                                                                        |
|  PASS  | 747: Move Operator (copy[i] == i)                                                                                                |
|  PASS  | 747: Move Operator (copy[i] == i)                                                                                                |
|  PASS  | 747: Move Operator (copy[i] == i)                                                                                                |
|  PASS  | 747: Move Operator (copy[i] == i)                                                                                                |
|  PASS  | 747: Move Operator (copy[i] == i)                                                                                                |
|  PASS  | 754: Index Operator (test[0] == 0)                                                                                               |
|  PASS  | 755: Index Operator (test[1] == 1)                                                                                               |
|  PASS  | 756: Index Operator (test[2] == 2)                                                                                               |
|  PASS  | 757: Index Operator (test[3] == 3)                                                                                               |
|  PASS  | 758: Index Operator (test[4] == 4)                                                                                               |
|  PASS  | 759: Index Operator (test[5])                                                                                                    |
|  PASS  | 765: Const Index Operator (test[0] == 0)                                                                                         |
|  PASS  | 766: Const Index Operator (test[1] == 1)                                                                                         |
|  PASS  | 767: Const Index Operator (test[2] == 2)                                                                                         |
|  PASS  | 768: Const Index Operator (test[3] == 3)                                                                                         |
|  PASS  | 769: Const Index Operator (test[4] == 4)                                                                                         |
|  PASS  | 770: Const Index Operator (test[5])                                                                                              |
|  PASS  | 776: Get Size (test.get_size() == 0)                                                                                             |
|  PASS  | 779: Get Size (test.get_size() == 5)                                                                                             |
|  PASS  | 786: Resize (test.get_size() == 5)                                                                                               |
|  PASS  | 788: Resize (test.get_size() == 10)                                                                                              |
|  PASS  | 790: Resize (test.get_size() == 0)                                                                                               |
|  PASS  | 792: Resize (test.get_size() == 20)                                                                                              |
|  PASS  | 800: Add Copy (test.get_size() == 1)                                                                                             |
|  PASS  | 801: Add Copy (test[0] == "5")                                                                                                   |
|  PASS  | 804: Add Copy (test.get_size() == 2)                                                                                             |
|  PASS  | 805: Add Copy (test[1] == "10")                                                                                                  |
|  PASS  | 813: Add Move (test.get_size() == 1)                                                                                             |
|  PASS  | 814: Add Move (test[0] == "5")                                                                                                   |
|  PASS  | 817: Add Move (test.get_size() == 2)                                                                                             |
|  PASS  | 818: Add Move (test[1] == "10")                                                                                                  |
|  PASS  | 826: Add Range (test.get_size() == 5)                                                                                            |
|  PASS  | 827: Add Range (test[0] == 0)                                                                                                    |
|  PASS  | 828: Add Range (test[1] == 1)                                                                                                    |
|  PASS  | 829: Add Range (test[2] == 2)                                                                                                    |
|  PASS  | 830: Add Range (test[3] == 3)                                                                                                    |
|  PASS  | 831: Add Range (test[4] == 4)                                                                                                    |
|  PASS  | 838: Insert Index Copy (test.get_size() == 6)                                                                                    |
|  PASS  | 839: Insert Index Copy (test[0] == 0)                                                                                            |
|  PASS  | 840: Insert Index Copy (test[1] == 1)                                                                                            |
|  PASS  | 841: Insert Index Copy (test[2] == 5)                                                                                            |
|  PASS  | 842: Insert Index Copy (test[3] == 2)                                                                                            |
|  PASS  | 843: Insert Index Copy (test[4] == 3)                                                                                            |
|  PASS  | 844: Insert Index Copy (test[5] == 4)                                                                                            |
|  PASS  | 846: Insert Index Copy (test.get_size() == 7)                                                                                    |
|  PASS  | 847: Insert Index Copy (test[0] == 6)                                                                                            |
|  PASS  | 848: Insert Index Copy (test[1] == 0)                                                                                            |
|  PASS  | 849: Insert Index Copy (test[2] == 1)                                                                                            |
|  PASS  | 850: Insert Index Copy (test[3] == 5)                                                                                            |
|  PASS  | 851: Insert Index Copy (test[4] == 2)                                                                                            |
|  PASS  | 852: Insert Index Copy (test[5] == 3)                                                                                            |
|  PASS  | 853: Insert Index Copy (test[6] == 4)                                                                                            |
|  PASS  | 855: Insert Index Copy (test.get_size() == 8)                                                                                    |
|  PASS  | 856: Insert Index Copy (test[0] == 6)                                                                                            |
|  PASS  | 857: Insert Index Copy (test[1] == 0)                                                                                            |
|  PASS  | 858: Insert Index Copy (test[2] == 1)                                                                                            |
|  PASS  | 859: Insert Index Copy (test[3] == 5)                                                                                            |
|  PASS  | 860: Insert Index Copy (test[4] == 2)                                                                                            |
|  PASS  | 861: Insert Index Copy (test[5] == 3)                                                                                            |
|  PASS  | 862: Insert Index Copy (test[6] == 4)                                                                                            |
|  PASS  | 863: Insert Index Copy (test[7] == 7)                                                                                            |
|  PASS  | 871: Insert Index Move (test.get_size() == 6)                                                                                    |
|  PASS  | 872: Insert Index Move (test[0] == "0")                                                                                          |
|  PASS  | 873: Insert Index Move (test[1] == "1")                                                                                          |
|  PASS  | 874: Insert Index Move (test[2] == "5")                                                                                          |
|  PASS  | 875: Insert Index Move (test[3] == "2")                                                                                          |
|  PASS  | 876: Insert Index Move (test[4] == "3")                                                                                          |
|  PASS  | 877: Insert Index Move (test[5] == "4")                                                                                          |
|  PASS  | 880: Insert Index Move (test.get_size() == 7)                                                                                    |
|  PASS  | 881: Insert Index Move (test[0] == "6")                                                                                          |
|  PASS  | 882: Insert Index Move (test[1] == "0")                                                                                          |
|  PASS  | 883: Insert Index Move (test[2] == "1")                                                                                          |
|  PASS  | 884: Insert Index Move (test[3] == "5")                                                                                          |
|  PASS  | 885: Insert Index Move (test[4] == "2")                                                                                          |
|  PASS  | 886: Insert Index Move (test[5] == "3")                                                                                          |
|  PASS  | 887: Insert Index Move (test[6] == "4")                                                                                          |
|  PASS  | 890: Insert Index Move (test.get_size() == 8)                                                                                    |
|  PASS  | 891: Insert Index Move (test[0] == "6")                                                                                          |
|  PASS  | 892: Insert Index Move (test[1] == "0")                                                                                          |
|  PASS  | 893: Insert Index Move (test[2] == "1")                                                                                          |
|  PASS  | 894: Insert Index Move (test[3] == "5")                                                                                          |
|  PASS  | 895: Insert Index Move (test[4] == "2")                                                                                          |
|  PASS  | 896: Insert Index Move (test[5] == "3")                                                                                          |
|  PASS  | 897: Insert Index Move (test[6] == "4")                                                                                          |
|  PASS  | 898: Insert Index Move (test[7] == "7")                                                                                          |
|  PASS  | 906: Insert Iterator Copy (test.get_size() == 8)                                                                                 |
|  PASS  | 907: Insert Iterator Copy (test[0] == 0)                                                                                         |
|  PASS  | 908: Insert Iterator Copy (test[1] == 1)                                                                                         |
|  PASS  | 909: Insert Iterator Copy (test[2] == 5)                                                                                         |
|  PASS  | 910: Insert Iterator Copy (test[3] == 6)                                                                                         |
|  PASS  | 911: Insert Iterator Copy (test[4] == 7)                                                                                         |
|  PASS  | 912: Insert Iterator Copy (test[5] == 2)                                                                                         |
|  PASS  | 913: Insert Iterator Copy (test[6] == 3)                                                                                         |
|  PASS  | 914: Insert Iterator Copy (test[7] == 4)                                                                                         |
|  PASS  | 922: Insert Iterator Move (test.get_size() == 8)                                                                                 |
|  PASS  | 923: Insert Iterator Move (test[0] == "0")                                                                                       |
|  PASS  | 924: Insert Iterator Move (test[1] == "1")                                                                                       |
|  PASS  | 925: Insert Iterator Move (test[2] == "5")                                                                                       |
|  PASS  | 926: Insert Iterator Move (test[3] == "6")                                                                                       |
|  PASS  | 927: Insert Iterator Move (test[4] == "7")                                                                                       |
|  PASS  | 928: Insert Iterator Move (test[5] == "2")                                                                                       |
|  PASS  | 929: Insert Iterator Move (test[6] == "3")                                                                                       |
|  PASS  | 930: Insert Iterator Move (test[7] == "4")                                                                                       |
|  PASS  | 938: Insert Index Range (test.get_size() == 8)                                                                                   |
|  PASS  | 939: Insert Index Range (test[0] == 0)                                                                                           |
|  PASS  | 940: Insert Index Range (test[1] == 1)                                                                                           |
|  PASS  | 941: Insert Index Range (test[2] == 5)                                                                                           |
|  PASS  | 942: Insert Index Range (test[3] == 6)                                                                                           |
|  PASS  | 943: Insert Index Range (test[4] == 7)                                                                                           |
|  PASS  | 944: Insert Index Range (test[5] == 2)                                                                                           |
|  PASS  | 945: Insert Index Range (test[6] == 3)                                                                                           |
|  PASS  | 946: Insert Index Range (test[7] == 4)                                                                                           |
|  PASS  | 954: Insert Iterator Range (test.get_size() == 8)                                                                                |
|  PASS  | 955: Insert Iterator Range (test[0] == 0)                                                                                        |
|  PASS  | 956: Insert Iterator Range (test[1] == 1)                                                                                        |
|  PASS  | 957: Insert Iterator Range (test[2] == 5)                                                                                        |
|  PASS  | 958: Insert Iterator Range (test[3] == 6)                                                                                        |
|  PASS  | 959: Insert Iterator Range (test[4] == 7)                                                                                        |
|  PASS  | 960: Insert Iterator Range (test[5] == 2)                                                                                        |
|  PASS  | 961: Insert Iterator Range (test[6] == 3)                                                                                        |
|  PASS  | 962: Insert Iterator Range (test[7] == 4)                                                                                        |
|  PASS  | 969: Remove Index (test.get_size() == 4)                                                                                         |
|  PASS  | 970: Remove Index (test[0] == 0)                                                                                                 |
|  PASS  | 971: Remove Index (test[1] == 1)                                                                                                 |
|  PASS  | 972: Remove Index (test[2] == 3)                                                                                                 |
|  PASS  | 973: Remove Index (test[3] == 4)                                                                                                 |
|  PASS  | 975: Remove Index (test.get_size() == 3)                                                                                         |
|  PASS  | 976: Remove Index (test[0] == 1)                                                                                                 |
|  PASS  | 977: Remove Index (test[1] == 3)                                                                                                 |
|  PASS  | 978: Remove Index (test[2] == 4)                                                                                                 |
|  PASS  | 980: Remove Index (test.get_size() == 2)                                                                                         |
|  PASS  | 981: Remove Index (test[0] == 1)                                                                                                 |
|  PASS  | 982: Remove Index (test[1] == 3)                                                                                                 |
|  PASS  | 984: Remove Index (test.get_size() == 1)                                                                                         |
|  PASS  | 985: Remove Index (test[0] == 1)                                                                                                 |
|  PASS  | 987: Remove Index (test.get_size() == 0)                                                                                         |
|  PASS  | 994: Remove Iterator (test.get_size() == 4)                                                                                      |
|  PASS  | 995: Remove Iterator (test[0] == 0)                                                                                              |
|  PASS  | 996: Remove Iterator (test[1] == 1)                                                                                              |
|  PASS  | 997: Remove Iterator (test[2] == 3)                                                                                              |
|  PASS  | 998: Remove Iterator (test[3] == 4)                                                                                              |
|  PASS  | 1000: Remove Iterator (test.get_size() == 3)                                                                                     |
|  PASS  | 1001: Remove Iterator (test[0] == 1)                                                                                             |
|  PASS  | 1002: Remove Iterator (test[1] == 3)                                                                                             |
|  PASS  | 1003: Remove Iterator (test[2] == 4)                                                                                             |
|  PASS  | 1005: Remove Iterator (test.get_size() == 2)                                                                                     |
|  PASS  | 1006: Remove Iterator (test[0] == 1)                                                                                             |
|  PASS  | 1007: Remove Iterator (test[1] == 3)                                                                                             |
|  PASS  | 1009: Remove Iterator (test.get_size() == 1)                                                                                     |
|  PASS  | 1010: Remove Iterator (test[0] == 1)                                                                                             |
|  PASS  | 1012: Remove Iterator (test.get_size() == 0)                                                                                     |
|  PASS  | 1018: Remove Index Range (test.remove(0, 0))                                                                                     |
|  PASS  | 1019: Remove Index Range (test.remove(5, 1))                                                                                     |
|  PASS  | 1020: Remove Index Range (test.remove(0, 6))                                                                                     |
|  PASS  | 1022: Remove Index Range (test.get_size() == 2)                                                                                  |
|  PASS  | 1023: Remove Index Range (test[0] == 0)                                                                                          |
|  PASS  | 1024: Remove Index Range (test[1] == 4)                                                                                          |
|  PASS  | 1026: Remove Index Range (test.get_size() == 1)                                                                                  |
|  PASS  | 1027: Remove Index Range (test[0] == 4)                                                                                          |
|  PASS  | 1028: Remove Index Range (test.get_size() == 1)                                                                                  |
|  PASS  | 1029: Remove Index Range (test[0] == 4)                                                                                          |
|  PASS  | 1031: Remove Index Range (test.get_size() == 0)                                                                                  |
|  PASS  | 1037: Remove Iterator Range (test.remove(test.begin(), test.begin()))                                                            |
|  PASS  | 1038: Remove Iterator Range (test.remove(test.end(), test.end()))                                                                |
|  PASS  | 1039: Remove Iterator Range (test.remove(test.end(), test.begin()))                                                              |
|  PASS  | 1041: Remove Iterator Range (test.get_size() == 2)                                                                               |
|  PASS  | 1042: Remove Iterator Range (test[0] == 0)                                                                                       |
|  PASS  | 1043: Remove Iterator Range (test[1] == 4)                                                                                       |
|  PASS  | 1045: Remove Iterator Range (test.get_size() == 1)                                                                               |
|  PASS  | 1046: Remove Iterator Range (test[0] == 4)                                                                                       |
|  PASS  | 1047: Remove Iterator Range (test.get_size() == 1)                                                                               |
|  PASS  | 1048: Remove Iterator Range (test[0] == 4)                                                                                       |
|  PASS  | 1050: Remove Iterator Range (test.get_size() == 0)                                                                               |
|  PASS  | 1056: Is Empty (test.is_empty())                                                                                                 |
|  PASS  | 1058: Is Empty (!test.is_empty())                                                                                                |
|  PASS  | 1060: Is Empty (test.is_empty())                                                                                                 |
|  PASS  | 1066: At (test.at(0) == 0)                                                                                                       |
|  PASS  | 1067: At (test.at(1) == 1)                                                                                                       |
|  PASS  | 1068: At (test.at(2) == 2)                                                                                                       |
|  PASS  | 1069: At (test.at(3) == 3)                                                                                                       |
|  PASS  | 1070: At (test.at(4) == 4)                                                                                                       |
|  PASS  | 1071: At (test.at(5))                                                                                                            |
|  PASS  | 1073: At (test.at(0) == 5)                                                                                                       |
|  PASS  | 1079: Const At (test.at(0) == 0)                                                                                                 |
|  PASS  | 1080: Const At (test.at(1) == 1)                                                                                                 |
|  PASS  | 1081: Const At (test.at(2) == 2)                                                                                                 |
|  PASS  | 1082: Const At (test.at(3) == 3)                                                                                                 |
|  PASS  | 1083: Const At (test.at(4) == 4)                                                                                                 |
|  PASS  | 1084: Const At (test.at(5))                                                                                                      |
|  PASS  | 1091: Sub (sub.get_size() == 2)                                                                                                  |
|  PASS  | 1092: Sub (sub[0] == 2)                                                                                                          |
|  PASS  | 1093: Sub (sub[1] == 3)                                                                                                          |
|  PASS  | 1099: Find (test.find(0) == test.begin())                                                                                        |
|  PASS  | 1100: Find (test.find(1) == test.begin() + 1)                                                                                    |
|  PASS  | 1101: Find (test.find(2) == test.begin() + 2)                                                                                    |
|  PASS  | 1102: Find (test.find(3) == test.begin() + 3)                                                                                    |
|  PASS  | 1103: Find (test.find(4) == test.begin() + 4)                                                                                    |
|  PASS  | 1104: Find (test.find(5) == test.end())                                                                                          |
|  PASS  | 1110: Const Find (test.find(0) == test.begin())                                                                                  |
|  PASS  | 1111: Const Find (test.find(1) == test.begin() + 1)                                                                              |
|  PASS  | 1112: Const Find (test.find(2) == test.begin() + 2)                                                                              |
|  PASS  | 1113: Const Find (test.find(3) == test.begin() + 3)                                                                              |
|  PASS  | 1114: Const Find (test.find(4) == test.begin() + 4)                                                                              |
|  PASS  | 1115: Const Find (test.find(5) == test.end())                                                                                    |
|  PASS  | 1121: Contains (test.contains(0))                                                                                                |
|  PASS  | 1122: Contains (test.contains(1))                                                                                                |
|  PASS  | 1123: Contains (test.contains(2))                                                                                                |
|  PASS  | 1124: Contains (test.contains(3))                                                                                                |
|  PASS  | 1125: Contains (test.contains(4))                                                                                                |
|  PASS  | 1126: Contains (!test.contains(5))                                                                                               |
|  PASS  | 1133: Clear (test.get_size() == 0)                                                                                               |
|  PASS  | 1139: Begin (*test.begin() == 0)                                                                                                 |
|  PASS  | 1145: Const Begin (*test.begin() == 0)                                                                                           |
|  PASS  | 1151: End (test.end() == test.begin() + 5)                                                                                       |
|  PASS  | 1157: Const End (test.end() == test.begin() + 5)                                                                                 |
|  PASS  | 1163: Reverse Begin (*test.rbegin() == 4)                                                                                        |
|  PASS  | 1169: Reverse End (test.rend() == test.rbegin() + 5)                                                                             |
|  PASS  | 1175: Const Reverse Begin (*test.rbegin() == 4)                                                                                  |
|  PASS  | 1181: Const Reverse End (test.rend() == test.rbegin() + 5)                                                                       |

## Map::Iterator
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 13: Dereference Operator ((*it == Pair<int, int>(0, 0)))                                                                         |
|  PASS  | 15: Dereference Operator (*it)                                                                                                   |
|  PASS  | 23: Member Access Operator (it->first == 0)                                                                                      |
|  PASS  | 24: Member Access Operator (it->second == 0)                                                                                     |
|  PASS  | 26: Member Access Operator (it->first)                                                                                           |
|  PASS  | 27: Member Access Operator (it->second)                                                                                          |
|  PASS  | 36: Increment Operator ((*it == Pair<int, int>(0, 0)) || (*it == Pair<int, int>(1, 1)))                                          |
|  PASS  | 38: Increment Operator ((*it == Pair<int, int>(0, 0)) || (*it == Pair<int, int>(1, 1)))                                          |
|  PASS  | 40: Increment Operator (*it)                                                                                                     |
|  PASS  | 49: Addition Operator ((*(it + 0) == Pair<int, int>(0, 0)) || (*(it + 0) == Pair<int, int>(1, 1)))                               |
|  PASS  | 50: Addition Operator ((*(it + 1) == Pair<int, int>(0, 0)) || (*(it + 1) == Pair<int, int>(1, 1)))                               |
|  PASS  | 51: Addition Operator (*(it + 2))                                                                                                |
|  PASS  | 52: Addition Operator (it + 2 == map.end())                                                                                      |
|  PASS  | 62: Equal Operator (it == it2)                                                                                                   |
|  PASS  | 64: Equal Operator (!(it == it2))                                                                                                |
|  PASS  | 74: Not Equal Operator (!(it != it2))                                                                                            |
|  PASS  | 76: Not Equal Operator (it != it2)                                                                                               |

## Map::ConstIterator
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 86: Dereference Operator ((*it == Pair<int, int>(0, 0)))                                                                         |
|  PASS  | 88: Dereference Operator (*it)                                                                                                   |
|  PASS  | 95: Member Access Operator (it->first == 0)                                                                                      |
|  PASS  | 96: Member Access Operator (it->second == 0)                                                                                     |
|  PASS  | 98: Member Access Operator (it->first)                                                                                           |
|  PASS  | 99: Member Access Operator (it->second)                                                                                          |
|  PASS  | 106: Increment Operator ((*it == Pair<int, int>(0, 0)) || (*it == Pair<int, int>(1, 1)))                                         |
|  PASS  | 108: Increment Operator ((*it == Pair<int, int>(0, 0)) || (*it == Pair<int, int>(1, 1)))                                         |
|  PASS  | 110: Increment Operator (*it)                                                                                                    |
|  PASS  | 117: Addition Operator ((*(it + 0) == Pair<int, int>(0, 0)) || (*(it + 0) == Pair<int, int>(1, 1)))                              |
|  PASS  | 118: Addition Operator ((*(it + 1) == Pair<int, int>(0, 0)) || (*(it + 1) == Pair<int, int>(1, 1)))                              |
|  PASS  | 119: Addition Operator (*(it + 2))                                                                                               |
|  PASS  | 120: Addition Operator (it + 2 == map.end())                                                                                     |
|  PASS  | 128: Equal Operator (it == it2)                                                                                                  |
|  PASS  | 130: Equal Operator (!(it == it2))                                                                                               |
|  PASS  | 138: Not Equal Operator (!(it != it2))                                                                                           |
|  PASS  | 140: Not Equal Operator (it != it2)                                                                                              |

## Map
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 149: Default Constructor (map.get_capacity() == 0)                                                                               |
|  PASS  | 150: Default Constructor (map.get_size() == 0)                                                                                   |
|  PASS  | 156: Capacity Constructor (map.get_capacity() == 10)                                                                             |
|  PASS  | 157: Capacity Constructor (map.get_size() == 0)                                                                                  |
|  PASS  | 159: Capacity Constructor (map2.get_capacity() == 0)                                                                             |
|  PASS  | 160: Capacity Constructor (map2.get_size() == 0)                                                                                 |
|  PASS  | 166: Initializer List Constructor (map.get_capacity() >= 3)                                                                      |
|  PASS  | 167: Initializer List Constructor (map.get_size() == 3)                                                                          |
|  PASS  | 168: Initializer List Constructor (map[0] == 0)                                                                                  |
|  PASS  | 169: Initializer List Constructor (map[1] == 1)                                                                                  |
|  PASS  | 170: Initializer List Constructor (map[2] == 2)                                                                                  |
|  PASS  | 177: Copy Constructor (map2.get_capacity() >= 3)                                                                                 |
|  PASS  | 178: Copy Constructor (map2.get_size() == 3)                                                                                     |
|  PASS  | 179: Copy Constructor (map2[0] == 0)                                                                                             |
|  PASS  | 180: Copy Constructor (map2[1] == 1)                                                                                             |
|  PASS  | 181: Copy Constructor (map2[2] == 2)                                                                                             |
|  PASS  | 188: Move Constructor (map2.get_capacity() >= 3)                                                                                 |
|  PASS  | 189: Move Constructor (map2.get_size() == 3)                                                                                     |
|  PASS  | 190: Move Constructor (map2[0] == 0)                                                                                             |
|  PASS  | 191: Move Constructor (map2[1] == 1)                                                                                             |
|  PASS  | 192: Move Constructor (map2[2] == 2)                                                                                             |
|  PASS  | 200: Copy Assignment Operator (map2.get_capacity() >= 3)                                                                         |
|  PASS  | 201: Copy Assignment Operator (map2.get_size() == 3)                                                                             |
|  PASS  | 202: Copy Assignment Operator (map2[0] == 0)                                                                                     |
|  PASS  | 203: Copy Assignment Operator (map2[1] == 1)                                                                                     |
|  PASS  | 204: Copy Assignment Operator (map2[2] == 2)                                                                                     |
|  PASS  | 212: Move Assignment Operator (map2.get_capacity() >= 3)                                                                         |
|  PASS  | 213: Move Assignment Operator (map2.get_size() == 3)                                                                             |
|  PASS  | 214: Move Assignment Operator (map2[0] == 0)                                                                                     |
|  PASS  | 215: Move Assignment Operator (map2[1] == 1)                                                                                     |
|  PASS  | 216: Move Assignment Operator (map2[2] == 2)                                                                                     |
|  PASS  | 222: Index Operator (map[0] = 0)                                                                                                 |
|  PASS  | 223: Index Operator (map[1] = 1)                                                                                                 |
|  PASS  | 224: Index Operator (map[2] = 3)                                                                                                 |
|  PASS  | 225: Index Operator (map[2] = 2)                                                                                                 |
|  PASS  | 226: Index Operator (map.get_capacity() >= 3)                                                                                    |
|  PASS  | 227: Index Operator (map.get_size() == 3)                                                                                        |
|  PASS  | 228: Index Operator (map[0] == 0)                                                                                                |
|  PASS  | 229: Index Operator (map[1] == 1)                                                                                                |
|  PASS  | 230: Index Operator (map[2] == 2)                                                                                                |
|  PASS  | 240: Const Index Operator (map2[0] == 0)                                                                                         |
|  PASS  | 241: Const Index Operator (map2[1] == 1)                                                                                         |
|  PASS  | 242: Const Index Operator (map2[2] == 2)                                                                                         |
|  PASS  | 248: Get Capacity (map.get_capacity() == 0)                                                                                      |
|  PASS  | 250: Get Capacity (map.get_capacity() >= 1)                                                                                      |
|  PASS  | 252: Get Capacity (map.get_capacity() >= 2)                                                                                      |
|  PASS  | 254: Get Capacity (map.get_capacity() >= 3)                                                                                      |
|  PASS  | 260: Get Size (map.get_size() == 0)                                                                                              |
|  PASS  | 262: Get Size (map.get_size() == 1)                                                                                              |
|  PASS  | 264: Get Size (map.get_size() == 2)                                                                                              |
|  PASS  | 266: Get Size (map.get_size() == 3)                                                                                              |
|  PASS  | 273: Reserve (map.get_capacity() >= 10)                                                                                          |
|  PASS  | 274: Reserve (map.get_size() == 0)                                                                                               |
|  PASS  | 277: Reserve (map.get_capacity() >= 10)                                                                                          |
|  PASS  | 278: Reserve (map.get_size() == 1)                                                                                               |
|  PASS  | 288: Add Copy (map.get_capacity() >= 2)                                                                                          |
|  PASS  | 289: Add Copy (map.get_size() == 2)                                                                                              |
|  PASS  | 290: Add Copy (map["0"] == "0")                                                                                                  |
|  PASS  | 291: Add Copy (map["1"] == "1")                                                                                                  |
|  PASS  | 292: Add Copy (map.add("0", "2"))                                                                                                |
|  PASS  | 302: Add Move (map.get_capacity() >= 2)                                                                                          |
|  PASS  | 303: Add Move (map.get_size() == 2)                                                                                              |
|  PASS  | 304: Add Move (map["0"] == "0")                                                                                                  |
|  PASS  | 305: Add Move (map["1"] == "1")                                                                                                  |
|  PASS  | 307: Add Move (map.add("0", std::move(str)))                                                                                     |
|  PASS  | 313: Remove (map.remove(0) == false)                                                                                             |
|  PASS  | 317: Remove (map.remove(3) == false)                                                                                             |
|  PASS  | 319: Remove (map.get_capacity() >= 2)                                                                                            |
|  PASS  | 320: Remove (map.get_size() == 2)                                                                                                |
|  PASS  | 321: Remove (map[0] == 0)                                                                                                        |
|  PASS  | 322: Remove (map[2] == 2)                                                                                                        |
|  PASS  | 324: Remove (map.get_capacity() >= 2)                                                                                            |
|  PASS  | 325: Remove (map.get_size() == 1)                                                                                                |
|  PASS  | 326: Remove (map[2] == 2)                                                                                                        |
|  PASS  | 328: Remove (map.get_capacity() >= 2)                                                                                            |
|  PASS  | 329: Remove (map.get_size() == 0)                                                                                                |
|  PASS  | 335: Is Empty (map.is_empty())                                                                                                   |
|  PASS  | 337: Is Empty (!map.is_empty())                                                                                                  |
|  PASS  | 339: Is Empty (map.is_empty())                                                                                                   |
|  PASS  | 348: At (map.at(0) == 0)                                                                                                         |
|  PASS  | 349: At (map.at(1) == 1)                                                                                                         |
|  PASS  | 350: At (map.at(2) == 2)                                                                                                         |
|  PASS  | 351: At (map.at(3))                                                                                                              |
|  PASS  | 361: Const At (map2.at(0) == 0)                                                                                                  |
|  PASS  | 362: Const At (map2.at(1) == 1)                                                                                                  |
|  PASS  | 363: Const At (map2.at(2) == 2)                                                                                                  |
|  PASS  | 364: Const At (map2.at(3))                                                                                                       |
|  PASS  | 373: Find (map.find(0) != map.end())                                                                                             |
|  PASS  | 374: Find (map.find(1) != map.end())                                                                                             |
|  PASS  | 375: Find (map.find(2) != map.end())                                                                                             |
|  PASS  | 376: Find (map.find(3) == map.end())                                                                                             |
|  PASS  | 386: Const Find (map2.find(0) != map2.end())                                                                                     |
|  PASS  | 387: Const Find (map2.find(1) != map2.end())                                                                                     |
|  PASS  | 388: Const Find (map2.find(2) != map2.end())                                                                                     |
|  PASS  | 389: Const Find (map2.find(3) == map2.end())                                                                                     |
|  PASS  | 398: Contains (map.contains(0))                                                                                                  |
|  PASS  | 399: Contains (map.contains(1))                                                                                                  |
|  PASS  | 400: Contains (map.contains(2))                                                                                                  |
|  PASS  | 401: Contains (!map.contains(3))                                                                                                 |
|  PASS  | 411: Clear (map.get_capacity() >= 3)                                                                                             |
|  PASS  | 412: Clear (map.get_size() == 0)                                                                                                 |
|  PASS  | 421: Begin ((*it == Pair<int, int>(0, 0)) || (*it == Pair<int, int>(1, 1)))                                                      |
|  PASS  | 423: Begin ((*it == Pair<int, int>(0, 0)) || (*it == Pair<int, int>(1, 1)))                                                      |
|  PASS  | 425: Begin (*it)                                                                                                                 |
|  PASS  | 427: Begin (map2.begin() == map2.end())                                                                                          |
|  PASS  | 436: End (it == map.end())                                                                                                       |
|  PASS  | 438: End (map2.begin() == map2.end())                                                                                            |
|  PASS  | 445: Const Begin ((*it == Pair<int, int>(0, 0)) || (*it == Pair<int, int>(1, 1)))                                                |
|  PASS  | 447: Const Begin ((*it == Pair<int, int>(0, 0)) || (*it == Pair<int, int>(1, 1)))                                                |
|  PASS  | 449: Const Begin (*it)                                                                                                           |
|  PASS  | 451: Const Begin (map2.begin() == map2.end())                                                                                    |
|  PASS  | 458: Const End (it == map.end())                                                                                                 |
|  PASS  | 460: Const End (map2.begin() == map2.end())                                                                                      |

## Pair
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 13: Copy/Copy Constructor (first == "first")                                                                                     |
|  PASS  | 14: Copy/Copy Constructor (second == "second")                                                                                   |
|  PASS  | 15: Copy/Copy Constructor (pair.first == "first")                                                                                |
|  PASS  | 16: Copy/Copy Constructor (pair.second == "second")                                                                              |
|  PASS  | 24: Move/Copy Constructor (first == "")                                                                                          |
|  PASS  | 25: Move/Copy Constructor (second == "second")                                                                                   |
|  PASS  | 26: Move/Copy Constructor (pair.first == "first")                                                                                |
|  PASS  | 27: Move/Copy Constructor (pair.second == "second")                                                                              |
|  PASS  | 35: Copy/Move Constructor (first == "first")                                                                                     |
|  PASS  | 36: Copy/Move Constructor (second == "")                                                                                         |
|  PASS  | 37: Copy/Move Constructor (pair.first == "first")                                                                                |
|  PASS  | 38: Copy/Move Constructor (pair.second == "second")                                                                              |
|  PASS  | 46: Move/Move Constructor (first == "")                                                                                          |
|  PASS  | 47: Move/Move Constructor (second == "")                                                                                         |
|  PASS  | 48: Move/Move Constructor (pair.first == "first")                                                                                |
|  PASS  | 49: Move/Move Constructor (pair.second == "second")                                                                              |
|  PASS  | 56: Copy Constructor (pair.first == "First")                                                                                     |
|  PASS  | 57: Copy Constructor (pair.second == "Second")                                                                                   |
|  PASS  | 58: Copy Constructor (copy.first == "First")                                                                                     |
|  PASS  | 59: Copy Constructor (copy.second == "Second")                                                                                   |
|  PASS  | 66: Move Constructor (pair.first == "")                                                                                          |
|  PASS  | 67: Move Constructor (pair.second == "")                                                                                         |
|  PASS  | 68: Move Constructor (copy.first == "First")                                                                                     |
|  PASS  | 69: Move Constructor (copy.second == "Second")                                                                                   |
|  PASS  | 76: Copy Operator (pair.first == "First")                                                                                        |
|  PASS  | 77: Copy Operator (pair.second == "Second")                                                                                      |
|  PASS  | 78: Copy Operator (copy.first == "First")                                                                                        |
|  PASS  | 79: Copy Operator (copy.second == "Second")                                                                                      |
|  PASS  | 86: Move Operator (pair.first == "")                                                                                             |
|  PASS  | 87: Move Operator (pair.second == "")                                                                                            |
|  PASS  | 88: Move Operator (copy.first == "First")                                                                                        |
|  PASS  | 89: Move Operator (copy.second == "Second")                                                                                      |
|  PASS  | 96: Equal Operator (pair == copy)                                                                                                |
|  PASS  | 97: Equal Operator (copy == pair)                                                                                                |
|  PASS  | 99: Equal Operator (!(pair == pair2))                                                                                            |
|  PASS  | 106: Not Equal Operator (pair != copy)                                                                                           |
|  PASS  | 107: Not Equal Operator (copy != pair)                                                                                           |
|  PASS  | 109: Not Equal Operator (!(pair != pair2))                                                                                       |
|  PASS  | 116: Less Than Operator (pair < copy)                                                                                            |
|  PASS  | 117: Less Than Operator (!(copy < pair))                                                                                         |
|  PASS  | 119: Less Than Operator (!(pair < copy))                                                                                         |
|  PASS  | 120: Less Than Operator (!(copy < pair))                                                                                         |
|  PASS  | 127: Less Than or Equal To Operator (pair <= copy)                                                                               |
|  PASS  | 128: Less Than or Equal To Operator (!(copy <= pair))                                                                            |
|  PASS  | 130: Less Than or Equal To Operator (pair <= copy)                                                                               |
|  PASS  | 131: Less Than or Equal To Operator (copy <= pair)                                                                               |
|  PASS  | 138: Greater Than Operator (copy > pair)                                                                                         |
|  PASS  | 139: Greater Than Operator (!(pair > copy))                                                                                      |
|  PASS  | 141: Greater Than Operator (!(pair > copy))                                                                                      |
|  PASS  | 142: Greater Than Operator (!(copy > pair))                                                                                      |
|  PASS  | 149: Greater Than or Equal To Operator (copy >= pair)                                                                            |
|  PASS  | 150: Greater Than or Equal To Operator (!(pair >= copy))                                                                         |
|  PASS  | 152: Greater Than or Equal To Operator (pair >= copy)                                                                            |
|  PASS  | 153: Greater Than or Equal To Operator (copy >= pair)                                                                            |

## Queue
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 11: Default Constructor (test.get_size() == 0)                                                                                   |
|  PASS  | 21: Copy Constructor (copy.get_size() == 3)                                                                                      |
|  PASS  | 24: Copy Constructor (copy.pop() == i)                                                                                           |
|  PASS  | 24: Copy Constructor (copy.pop() == i)                                                                                           |
|  PASS  | 35: Move Constructor (copy.get_size() == 3)                                                                                      |
|  PASS  | 38: Move Constructor (copy.pop() == i)                                                                                           |
|  PASS  | 38: Move Constructor (copy.pop() == i)                                                                                           |
|  PASS  | 49: Copy Operator (copy.get_size() == 3)                                                                                         |
|  PASS  | 52: Copy Operator (copy.pop() == i)                                                                                              |
|  PASS  | 52: Copy Operator (copy.pop() == i)                                                                                              |
|  PASS  | 63: Move Operator (copy.get_size() == 3)                                                                                         |
|  PASS  | 66: Move Operator (copy.pop() == i)                                                                                              |
|  PASS  | 66: Move Operator (copy.pop() == i)                                                                                              |
|  PASS  | 73: Get Size (test.get_size() == 0)                                                                                              |
|  PASS  | 75: Get Size (test.get_size() == 1)                                                                                              |
|  PASS  | 77: Get Size (test.get_size() == 0)                                                                                              |
|  PASS  | 85: Push Copy (test.get_size() == 1)                                                                                             |
|  PASS  | 86: Push Copy (test.peek() == "5")                                                                                               |
|  PASS  | 89: Push Copy (test.get_size() == 2)                                                                                             |
|  PASS  | 90: Push Copy (test.pop() == "5")                                                                                                |
|  PASS  | 91: Push Copy (test.pop() == "10")                                                                                               |
|  PASS  | 99: Push Move (test.get_size() == 1)                                                                                             |
|  PASS  | 100: Push Move (test.peek() == "5")                                                                                              |
|  PASS  | 103: Push Move (test.get_size() == 2)                                                                                            |
|  PASS  | 104: Push Move (test.pop() == "5")                                                                                               |
|  PASS  | 105: Push Move (test.pop() == "10")                                                                                              |
|  PASS  | 111: Pop (test.pop())                                                                                                            |
|  PASS  | 115: Pop (test.pop() == 0)                                                                                                       |
|  PASS  | 116: Pop (test.pop() == 1)                                                                                                       |
|  PASS  | 117: Pop (test.pop() == 2)                                                                                                       |
|  PASS  | 118: Pop (test.pop())                                                                                                            |
|  PASS  | 124: Is Empty (test.is_empty())                                                                                                  |
|  PASS  | 126: Is Empty (!test.is_empty())                                                                                                 |
|  PASS  | 128: Is Empty (test.is_empty())                                                                                                  |
|  PASS  | 136: Clear (test.get_size() == 2)                                                                                                |
|  PASS  | 138: Clear (test.get_size() == 0)                                                                                                |

## Set::Iterator
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 13: Dereference Operator ((*it == 0))                                                                                            |
|  PASS  | 15: Dereference Operator (*it)                                                                                                   |
|  PASS  | 23: Member Access Operator (it->get_size() == 1)                                                                                 |
|  PASS  | 25: Member Access Operator (it->get_size())                                                                                      |
|  PASS  | 34: Increment Operator ((*it == 0) || (*it == 1))                                                                                |
|  PASS  | 36: Increment Operator ((*it == 0) || (*it == 1))                                                                                |
|  PASS  | 38: Increment Operator (*it)                                                                                                     |
|  PASS  | 47: Addition Operator ((*(it + 0) == 0) || (*(it + 0) == 1))                                                                     |
|  PASS  | 48: Addition Operator ((*(it + 1) == 0) || (*(it + 1) == 1))                                                                     |
|  PASS  | 49: Addition Operator (*(it + 2))                                                                                                |
|  PASS  | 50: Addition Operator (it + 2 == set.end())                                                                                      |
|  PASS  | 60: Equal Operator (it == it2)                                                                                                   |
|  PASS  | 62: Equal Operator (!(it == it2))                                                                                                |
|  PASS  | 72: Not Equal Operator (!(it != it2))                                                                                            |
|  PASS  | 74: Not Equal Operator (it != it2)                                                                                               |

## Set::ConstIterator
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 84: Dereference Operator ((*it == 0))                                                                                            |
|  PASS  | 86: Dereference Operator (*it)                                                                                                   |
|  PASS  | 93: Member Access Operator (it->get_size() == 1)                                                                                 |
|  PASS  | 95: Member Access Operator (it->get_size())                                                                                      |
|  PASS  | 102: Increment Operator ((*it == 0) || (*it == 1))                                                                               |
|  PASS  | 104: Increment Operator ((*it == 0) || (*it == 1))                                                                               |
|  PASS  | 106: Increment Operator (*it)                                                                                                    |
|  PASS  | 113: Addition Operator ((*(it + 0) == 0) || (*(it + 0) == 1))                                                                    |
|  PASS  | 114: Addition Operator ((*(it + 1) == 0) || (*(it + 1) == 1))                                                                    |
|  PASS  | 115: Addition Operator (*(it + 2))                                                                                               |
|  PASS  | 116: Addition Operator (it + 2 == set.end())                                                                                     |
|  PASS  | 124: Equal Operator (it == it2)                                                                                                  |
|  PASS  | 126: Equal Operator (!(it == it2))                                                                                               |
|  PASS  | 134: Not Equal Operator (!(it != it2))                                                                                           |
|  PASS  | 136: Not Equal Operator (it != it2)                                                                                              |

## Set
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 145: Default Constructor (set.get_capacity() == 0)                                                                               |
|  PASS  | 146: Default Constructor (set.get_size() == 0)                                                                                   |
|  PASS  | 152: Capacity Constructor (set.get_capacity() == 10)                                                                             |
|  PASS  | 153: Capacity Constructor (set.get_size() == 0)                                                                                  |
|  PASS  | 155: Capacity Constructor (set2.get_capacity() == 0)                                                                             |
|  PASS  | 156: Capacity Constructor (set2.get_size() == 0)                                                                                 |
|  PASS  | 162: Initializer List Constructor (set.get_capacity() >= 3)                                                                      |
|  PASS  | 163: Initializer List Constructor (set.get_size() == 3)                                                                          |
|  PASS  | 164: Initializer List Constructor (set.contains(0))                                                                              |
|  PASS  | 165: Initializer List Constructor (set.contains(1))                                                                              |
|  PASS  | 166: Initializer List Constructor (set.contains(2))                                                                              |
|  PASS  | 173: Copy Constructor (set2.get_capacity() >= 3)                                                                                 |
|  PASS  | 174: Copy Constructor (set2.get_size() == 3)                                                                                     |
|  PASS  | 175: Copy Constructor (set2.contains(0))                                                                                         |
|  PASS  | 176: Copy Constructor (set2.contains(1))                                                                                         |
|  PASS  | 177: Copy Constructor (set2.contains(2))                                                                                         |
|  PASS  | 184: Move Constructor (set2.get_capacity() >= 3)                                                                                 |
|  PASS  | 185: Move Constructor (set2.get_size() == 3)                                                                                     |
|  PASS  | 186: Move Constructor (set2.contains(0))                                                                                         |
|  PASS  | 187: Move Constructor (set2.contains(1))                                                                                         |
|  PASS  | 188: Move Constructor (set2.contains(2))                                                                                         |
|  PASS  | 196: Copy Assignment Operator (set2.get_capacity() >= 3)                                                                         |
|  PASS  | 197: Copy Assignment Operator (set2.get_size() == 3)                                                                             |
|  PASS  | 198: Copy Assignment Operator (set2.contains(0))                                                                                 |
|  PASS  | 199: Copy Assignment Operator (set2.contains(1))                                                                                 |
|  PASS  | 200: Copy Assignment Operator (set2.contains(2))                                                                                 |
|  PASS  | 208: Move Assignment Operator (set2.get_capacity() >= 3)                                                                         |
|  PASS  | 209: Move Assignment Operator (set2.get_size() == 3)                                                                             |
|  PASS  | 210: Move Assignment Operator (set2.contains(0))                                                                                 |
|  PASS  | 211: Move Assignment Operator (set2.contains(1))                                                                                 |
|  PASS  | 212: Move Assignment Operator (set2.contains(2))                                                                                 |
|  PASS  | 218: Index Operator (set.add(0))                                                                                                 |
|  PASS  | 219: Index Operator (set.add(1))                                                                                                 |
|  PASS  | 220: Index Operator (set.add(2))                                                                                                 |
|  PASS  | 221: Index Operator (set.add(2))                                                                                                 |
|  PASS  | 222: Index Operator (set.get_capacity() >= 3)                                                                                    |
|  PASS  | 223: Index Operator (set.get_size() == 3)                                                                                        |
|  PASS  | 224: Index Operator (set.contains(0))                                                                                            |
|  PASS  | 225: Index Operator (set.contains(1))                                                                                            |
|  PASS  | 226: Index Operator (set.contains(2))                                                                                            |
|  PASS  | 236: Const Index Operator (set2.contains(0))                                                                                     |
|  PASS  | 237: Const Index Operator (set2.contains(1))                                                                                     |
|  PASS  | 238: Const Index Operator (set2.contains(2))                                                                                     |
|  PASS  | 244: Get Capacity (set.get_capacity() == 0)                                                                                      |
|  PASS  | 246: Get Capacity (set.get_capacity() >= 1)                                                                                      |
|  PASS  | 248: Get Capacity (set.get_capacity() >= 2)                                                                                      |
|  PASS  | 250: Get Capacity (set.get_capacity() >= 3)                                                                                      |
|  PASS  | 256: Get Size (set.get_size() == 0)                                                                                              |
|  PASS  | 258: Get Size (set.get_size() == 1)                                                                                              |
|  PASS  | 260: Get Size (set.get_size() == 2)                                                                                              |
|  PASS  | 262: Get Size (set.get_size() == 3)                                                                                              |
|  PASS  | 269: Reserve (set.get_capacity() >= 10)                                                                                          |
|  PASS  | 270: Reserve (set.get_size() == 0)                                                                                               |
|  PASS  | 273: Reserve (set.get_capacity() >= 10)                                                                                          |
|  PASS  | 274: Reserve (set.get_size() == 1)                                                                                               |
|  PASS  | 281: Add (set.add(str) == true)                                                                                                  |
|  PASS  | 283: Add (set.add(str) == true)                                                                                                  |
|  PASS  | 284: Add (set.get_capacity() >= 2)                                                                                               |
|  PASS  | 285: Add (set.get_size() == 2)                                                                                                   |
|  PASS  | 286: Add (set.contains("0"))                                                                                                     |
|  PASS  | 287: Add (set.contains("1"))                                                                                                     |
|  PASS  | 288: Add (set.add("0") == false)                                                                                                 |
|  PASS  | 294: Remove (set.remove(0) == false)                                                                                             |
|  PASS  | 298: Remove (set.remove(3) == false)                                                                                             |
|  PASS  | 299: Remove (set.remove(1) == true)                                                                                              |
|  PASS  | 300: Remove (set.get_capacity() >= 2)                                                                                            |
|  PASS  | 301: Remove (set.get_size() == 2)                                                                                                |
|  PASS  | 302: Remove (set.contains(0))                                                                                                    |
|  PASS  | 303: Remove (set.contains(2))                                                                                                    |
|  PASS  | 304: Remove (set.remove(0) == true)                                                                                              |
|  PASS  | 305: Remove (set.get_capacity() >= 2)                                                                                            |
|  PASS  | 306: Remove (set.get_size() == 1)                                                                                                |
|  PASS  | 307: Remove (set.contains(2))                                                                                                    |
|  PASS  | 308: Remove (set.remove(2) == true)                                                                                              |
|  PASS  | 309: Remove (set.get_capacity() >= 2)                                                                                            |
|  PASS  | 310: Remove (set.get_size() == 0)                                                                                                |
|  PASS  | 316: Is Empty (set.is_empty())                                                                                                   |
|  PASS  | 318: Is Empty (!set.is_empty())                                                                                                  |
|  PASS  | 320: Is Empty (set.is_empty())                                                                                                   |
|  PASS  | 329: Find (set.find(0) != set.end())                                                                                             |
|  PASS  | 330: Find (set.find(1) != set.end())                                                                                             |
|  PASS  | 331: Find (set.find(2) != set.end())                                                                                             |
|  PASS  | 332: Find (set.find(3) == set.end())                                                                                             |
|  PASS  | 342: Const Find (set2.find(0) != set2.end())                                                                                     |
|  PASS  | 343: Const Find (set2.find(1) != set2.end())                                                                                     |
|  PASS  | 344: Const Find (set2.find(2) != set2.end())                                                                                     |
|  PASS  | 345: Const Find (set2.find(3) == set2.end())                                                                                     |
|  PASS  | 354: Contains (set.contains(0))                                                                                                  |
|  PASS  | 355: Contains (set.contains(1))                                                                                                  |
|  PASS  | 356: Contains (set.contains(2))                                                                                                  |
|  PASS  | 357: Contains (!set.contains(3))                                                                                                 |
|  PASS  | 367: Clear (set.get_capacity() >= 3)                                                                                             |
|  PASS  | 368: Clear (set.get_size() == 0)                                                                                                 |
|  PASS  | 377: Begin ((*it == 0) || (*it == 1))                                                                                            |
|  PASS  | 379: Begin ((*it == 0) || (*it == 1))                                                                                            |
|  PASS  | 381: Begin (*it)                                                                                                                 |
|  PASS  | 383: Begin (set2.begin() == set2.end())                                                                                          |
|  PASS  | 392: End (it == set.end())                                                                                                       |
|  PASS  | 394: End (set2.begin() == set2.end())                                                                                            |
|  PASS  | 401: Const Begin ((*it == 0) || (*it == 1))                                                                                      |
|  PASS  | 403: Const Begin ((*it == 0) || (*it == 1))                                                                                      |
|  PASS  | 405: Const Begin (*it)                                                                                                           |
|  PASS  | 407: Const Begin (set2.begin() == set2.end())                                                                                    |
|  PASS  | 414: Const End (it == set.end())                                                                                                 |
|  PASS  | 416: Const End (set2.begin() == set2.end())                                                                                      |

## Stack
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 11: Default Constructor (stack.get_capacity() == 0)                                                                              |
|  PASS  | 12: Default Constructor (stack.get_size() == 0)                                                                                  |
|  PASS  | 18: Capacity Constructor (stack.get_capacity() == 10)                                                                            |
|  PASS  | 19: Capacity Constructor (stack.get_size() == 0)                                                                                 |
|  PASS  | 21: Capacity Constructor (stack2.get_capacity() == 0)                                                                            |
|  PASS  | 22: Capacity Constructor (stack2.get_size() == 0)                                                                                |
|  PASS  | 32: Copy Constructor (stack2.get_capacity() == 10)                                                                               |
|  PASS  | 33: Copy Constructor (stack2.get_size() == 3)                                                                                    |
|  PASS  | 34: Copy Constructor (stack2.pop() == 3)                                                                                         |
|  PASS  | 35: Copy Constructor (stack2.pop() == 2)                                                                                         |
|  PASS  | 36: Copy Constructor (stack2.pop() == 1)                                                                                         |
|  PASS  | 37: Copy Constructor (stack2.get_size() == 0)                                                                                    |
|  PASS  | 47: Move Constructor (stack2.get_capacity() == 10)                                                                               |
|  PASS  | 48: Move Constructor (stack2.get_size() == 3)                                                                                    |
|  PASS  | 49: Move Constructor (stack2.pop() == 3)                                                                                         |
|  PASS  | 50: Move Constructor (stack2.pop() == 2)                                                                                         |
|  PASS  | 51: Move Constructor (stack2.pop() == 1)                                                                                         |
|  PASS  | 52: Move Constructor (stack2.get_size() == 0)                                                                                    |
|  PASS  | 63: Copy Assignment Operator (stack2.get_capacity() == 10)                                                                       |
|  PASS  | 64: Copy Assignment Operator (stack2.get_size() == 3)                                                                            |
|  PASS  | 65: Copy Assignment Operator (stack2.pop() == 3)                                                                                 |
|  PASS  | 66: Copy Assignment Operator (stack2.pop() == 2)                                                                                 |
|  PASS  | 67: Copy Assignment Operator (stack2.pop() == 1)                                                                                 |
|  PASS  | 68: Copy Assignment Operator (stack2.get_size() == 0)                                                                            |
|  PASS  | 79: Move Assignment Operator (stack2.get_capacity() == 10)                                                                       |
|  PASS  | 80: Move Assignment Operator (stack2.get_size() == 3)                                                                            |
|  PASS  | 81: Move Assignment Operator (stack2.pop() == 3)                                                                                 |
|  PASS  | 82: Move Assignment Operator (stack2.pop() == 2)                                                                                 |
|  PASS  | 83: Move Assignment Operator (stack2.pop() == 1)                                                                                 |
|  PASS  | 84: Move Assignment Operator (stack2.get_size() == 0)                                                                            |
|  PASS  | 90: Get Capacity (stack.get_capacity() == 10)                                                                                    |
|  PASS  | 92: Get Capacity (stack.get_capacity() == 20)                                                                                    |
|  PASS  | 98: Get Size (stack.get_size() == 0)                                                                                             |
|  PASS  | 100: Get Size (stack.get_size() == 1)                                                                                            |
|  PASS  | 102: Get Size (stack.get_size() == 2)                                                                                            |
|  PASS  | 104: Get Size (stack.get_size() == 3)                                                                                            |
|  PASS  | 106: Get Size (stack.get_size() == 2)                                                                                            |
|  PASS  | 108: Get Size (stack.get_size() == 1)                                                                                            |
|  PASS  | 110: Get Size (stack.get_size() == 0)                                                                                            |
|  PASS  | 119: Get Data (stack.get_data()[0] == 1)                                                                                         |
|  PASS  | 120: Get Data (stack.get_data()[1] == 2)                                                                                         |
|  PASS  | 121: Get Data (stack.get_data()[2] == 3)                                                                                         |
|  PASS  | 131: Const Get Data (stack2.get_data()[0] == 1)                                                                                  |
|  PASS  | 132: Const Get Data (stack2.get_data()[1] == 2)                                                                                  |
|  PASS  | 133: Const Get Data (stack2.get_data()[2] == 3)                                                                                  |
|  PASS  | 140: Reserve (stack.get_capacity() == 20)                                                                                        |
|  PASS  | 142: Reserve (stack.get_capacity() == 20)                                                                                        |
|  PASS  | 149: Push Copy (stack.get_size() == 1)                                                                                           |
|  PASS  | 150: Push Copy (stack.get_data()[0] == 1)                                                                                        |
|  PASS  | 152: Push Copy (stack.get_size() == 2)                                                                                           |
|  PASS  | 153: Push Copy (stack.get_data()[0] == 1)                                                                                        |
|  PASS  | 154: Push Copy (stack.get_data()[1] == 2)                                                                                        |
|  PASS  | 156: Push Copy (stack.get_size() == 3)                                                                                           |
|  PASS  | 157: Push Copy (stack.get_data()[0] == 1)                                                                                        |
|  PASS  | 158: Push Copy (stack.get_data()[1] == 2)                                                                                        |
|  PASS  | 159: Push Copy (stack.get_data()[2] == 3)                                                                                        |
|  PASS  | 166: Push Move (stack.get_size() == 1)                                                                                           |
|  PASS  | 167: Push Move (stack.get_data()[0] == 1)                                                                                        |
|  PASS  | 169: Push Move (stack.get_size() == 2)                                                                                           |
|  PASS  | 170: Push Move (stack.get_data()[0] == 1)                                                                                        |
|  PASS  | 171: Push Move (stack.get_data()[1] == 2)                                                                                        |
|  PASS  | 173: Push Move (stack.get_size() == 3)                                                                                           |
|  PASS  | 174: Push Move (stack.get_data()[0] == 1)                                                                                        |
|  PASS  | 175: Push Move (stack.get_data()[1] == 2)                                                                                        |
|  PASS  | 176: Push Move (stack.get_data()[2] == 3)                                                                                        |
|  PASS  | 185: Pop (stack.pop() == 3)                                                                                                      |
|  PASS  | 186: Pop (stack.pop() == 2)                                                                                                      |
|  PASS  | 187: Pop (stack.pop() == 1)                                                                                                      |
|  PASS  | 188: Pop (stack.get_size() == 0)                                                                                                 |
|  PASS  | 194: Is Empty (stack.is_empty())                                                                                                 |
|  PASS  | 196: Is Empty (!stack.is_empty())                                                                                                |
|  PASS  | 198: Is Empty (stack.is_empty())                                                                                                 |
|  PASS  | 207: Peek (stack.peek() == 3)                                                                                                    |
|  PASS  | 209: Peek (stack.peek() == 2)                                                                                                    |
|  PASS  | 211: Peek (stack.peek() == 1)                                                                                                    |
|  PASS  | 213: Peek (stack.get_size() == 0)                                                                                                |
|  PASS  | 223: Const Peek (stack2.peek() == 3)                                                                                             |
|  PASS  | 225: Const Peek (stack2.peek() == 2)                                                                                             |
|  PASS  | 227: Const Peek (stack2.peek() == 1)                                                                                             |
|  PASS  | 229: Const Peek (stack2.get_size() == 0)                                                                                         |
|  PASS  | 239: Clear (stack.get_size() == 0)                                                                                               |

## String::Iterator
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 13: Copy Constructor (*copy == 'a')                                                                                              |
|  PASS  | 14: Copy Constructor (*(copy + 1) == 'b')                                                                                        |
|  PASS  | 15: Copy Constructor (*(copy + 2) == 'c')                                                                                        |
|  PASS  | 16: Copy Constructor (copy + 3 == test.end())                                                                                    |
|  PASS  | 17: Copy Constructor (*++copy == 'b')                                                                                            |
|  PASS  | 18: Copy Constructor (*++copy == 'c')                                                                                            |
|  PASS  | 19: Copy Constructor (++copy == test.end())                                                                                      |
|  PASS  | 21: Copy Constructor (*copy++ == 'a')                                                                                            |
|  PASS  | 22: Copy Constructor (*copy++ == 'b')                                                                                            |
|  PASS  | 23: Copy Constructor (*copy++ == 'c')                                                                                            |
|  PASS  | 24: Copy Constructor (copy == test.end())                                                                                        |
|  PASS  | 32: Move Constructor (*copy == 'a')                                                                                              |
|  PASS  | 33: Move Constructor (*(copy + 1) == 'b')                                                                                        |
|  PASS  | 34: Move Constructor (*(copy + 2) == 'c')                                                                                        |
|  PASS  | 35: Move Constructor (copy + 3 == test.end())                                                                                    |
|  PASS  | 36: Move Constructor (*++copy == 'b')                                                                                            |
|  PASS  | 37: Move Constructor (*++copy == 'c')                                                                                            |
|  PASS  | 38: Move Constructor (++copy == test.end())                                                                                      |
|  PASS  | 41: Move Constructor (*copy++ == 'a')                                                                                            |
|  PASS  | 42: Move Constructor (*copy++ == 'b')                                                                                            |
|  PASS  | 43: Move Constructor (*copy++ == 'c')                                                                                            |
|  PASS  | 44: Move Constructor (copy == test.end())                                                                                        |
|  PASS  | 52: Copy Operator (*copy == 'a')                                                                                                 |
|  PASS  | 53: Copy Operator (*(copy + 1) == 'b')                                                                                           |
|  PASS  | 54: Copy Operator (*(copy + 2) == 'c')                                                                                           |
|  PASS  | 55: Copy Operator (copy + 3 == test.end())                                                                                       |
|  PASS  | 56: Copy Operator (*++copy == 'b')                                                                                               |
|  PASS  | 57: Copy Operator (*++copy == 'c')                                                                                               |
|  PASS  | 58: Copy Operator (++copy == test.end())                                                                                         |
|  PASS  | 60: Copy Operator (*copy++ == 'a')                                                                                               |
|  PASS  | 61: Copy Operator (*copy++ == 'b')                                                                                               |
|  PASS  | 62: Copy Operator (*copy++ == 'c')                                                                                               |
|  PASS  | 63: Copy Operator (copy == test.end())                                                                                           |
|  PASS  | 71: Move Operator (*copy == 'a')                                                                                                 |
|  PASS  | 72: Move Operator (*(copy + 1) == 'b')                                                                                           |
|  PASS  | 73: Move Operator (*(copy + 2) == 'c')                                                                                           |
|  PASS  | 74: Move Operator (copy + 3 == test.end())                                                                                       |
|  PASS  | 75: Move Operator (*++copy == 'b')                                                                                               |
|  PASS  | 76: Move Operator (*++copy == 'c')                                                                                               |
|  PASS  | 77: Move Operator (++copy == test.end())                                                                                         |
|  PASS  | 80: Move Operator (*copy++ == 'a')                                                                                               |
|  PASS  | 81: Move Operator (*copy++ == 'b')                                                                                               |
|  PASS  | 82: Move Operator (*copy++ == 'c')                                                                                               |
|  PASS  | 83: Move Operator (copy == test.end())                                                                                           |
|  PASS  | 90: Dereference Operator (*it == 'a')                                                                                            |
|  PASS  | 91: Dereference Operator (*(it + 1) == 'b')                                                                                      |
|  PASS  | 92: Dereference Operator (*(it + 2) == 'c')                                                                                      |
|  PASS  | 93: Dereference Operator (it + 3 == test.end())                                                                                  |
|  PASS  | 94: Dereference Operator (*++it == 'b')                                                                                          |
|  PASS  | 95: Dereference Operator (*++it == 'c')                                                                                          |
|  PASS  | 96: Dereference Operator (++it == test.end())                                                                                    |
|  PASS  | 98: Dereference Operator (*it++ == 'a')                                                                                          |
|  PASS  | 99: Dereference Operator (*it++ == 'b')                                                                                          |
|  PASS  | 100: Dereference Operator (*it++ == 'c')                                                                                         |
|  PASS  | 101: Dereference Operator (it == test.end())                                                                                     |
|  PASS  | 108: Increment Operator (*it == 'a')                                                                                             |
|  PASS  | 109: Increment Operator (*(it + 1) == 'b')                                                                                       |
|  PASS  | 110: Increment Operator (*(it + 2) == 'c')                                                                                       |
|  PASS  | 111: Increment Operator (it + 3 == test.end())                                                                                   |
|  PASS  | 112: Increment Operator (*++it == 'b')                                                                                           |
|  PASS  | 113: Increment Operator (*++it == 'c')                                                                                           |
|  PASS  | 114: Increment Operator (++it == test.end())                                                                                     |
|  PASS  | 116: Increment Operator (*it++ == 'a')                                                                                           |
|  PASS  | 117: Increment Operator (*it++ == 'b')                                                                                           |
|  PASS  | 118: Increment Operator (*it++ == 'c')                                                                                           |
|  PASS  | 119: Increment Operator (it == test.end())                                                                                       |
|  PASS  | 126: Addition Operator (*it == 'a')                                                                                              |
|  PASS  | 127: Addition Operator (*(it + 1) == 'b')                                                                                        |
|  PASS  | 128: Addition Operator (*(it + 2) == 'c')                                                                                        |
|  PASS  | 129: Addition Operator (it + 3 == test.end())                                                                                    |
|  PASS  | 130: Addition Operator (*++it == 'b')                                                                                            |
|  PASS  | 131: Addition Operator (*++it == 'c')                                                                                            |
|  PASS  | 132: Addition Operator (++it == test.end())                                                                                      |
|  PASS  | 134: Addition Operator (*it++ == 'a')                                                                                            |
|  PASS  | 135: Addition Operator (*it++ == 'b')                                                                                            |
|  PASS  | 136: Addition Operator (*it++ == 'c')                                                                                            |
|  PASS  | 137: Addition Operator (it == test.end())                                                                                        |
|  PASS  | 145: Equal Operator (it == copy)                                                                                                 |
|  PASS  | 146: Equal Operator (copy == it)                                                                                                 |
|  PASS  | 147: Equal Operator (it == test.begin())                                                                                         |
|  PASS  | 148: Equal Operator (test.begin() == it)                                                                                         |
|  PASS  | 149: Equal Operator (copy == test.begin())                                                                                       |
|  PASS  | 150: Equal Operator (test.begin() == copy)                                                                                       |
|  PASS  | 158: Not Equal Operator (!(it != copy))                                                                                          |
|  PASS  | 159: Not Equal Operator (!(copy != it))                                                                                          |
|  PASS  | 160: Not Equal Operator (!(it != test.begin()))                                                                                  |
|  PASS  | 161: Not Equal Operator (!(test.begin() != it))                                                                                  |
|  PASS  | 162: Not Equal Operator (!(copy != test.begin()))                                                                                |
|  PASS  | 163: Not Equal Operator (!(test.begin() != copy))                                                                                |

## String::ConstIterator
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 174: Copy Constructor (*copy == 'a')                                                                                             |
|  PASS  | 175: Copy Constructor (*(copy + 1) == 'b')                                                                                       |
|  PASS  | 176: Copy Constructor (*(copy + 2) == 'c')                                                                                       |
|  PASS  | 177: Copy Constructor (copy + 3 == test.end())                                                                                   |
|  PASS  | 178: Copy Constructor (*++copy == 'b')                                                                                           |
|  PASS  | 179: Copy Constructor (*++copy == 'c')                                                                                           |
|  PASS  | 180: Copy Constructor (++copy == test.end())                                                                                     |
|  PASS  | 182: Copy Constructor (*copy++ == 'a')                                                                                           |
|  PASS  | 183: Copy Constructor (*copy++ == 'b')                                                                                           |
|  PASS  | 184: Copy Constructor (*copy++ == 'c')                                                                                           |
|  PASS  | 185: Copy Constructor (copy == test.end())                                                                                       |
|  PASS  | 193: Move Constructor (*copy == 'a')                                                                                             |
|  PASS  | 194: Move Constructor (*(copy + 1) == 'b')                                                                                       |
|  PASS  | 195: Move Constructor (*(copy + 2) == 'c')                                                                                       |
|  PASS  | 196: Move Constructor (copy + 3 == test.end())                                                                                   |
|  PASS  | 197: Move Constructor (*++copy == 'b')                                                                                           |
|  PASS  | 198: Move Constructor (*++copy == 'c')                                                                                           |
|  PASS  | 199: Move Constructor (++copy == test.end())                                                                                     |
|  PASS  | 202: Move Constructor (*copy++ == 'a')                                                                                           |
|  PASS  | 203: Move Constructor (*copy++ == 'b')                                                                                           |
|  PASS  | 204: Move Constructor (*copy++ == 'c')                                                                                           |
|  PASS  | 205: Move Constructor (copy == test.end())                                                                                       |
|  PASS  | 213: Copy Operator (*copy == 'a')                                                                                                |
|  PASS  | 214: Copy Operator (*(copy + 1) == 'b')                                                                                          |
|  PASS  | 215: Copy Operator (*(copy + 2) == 'c')                                                                                          |
|  PASS  | 216: Copy Operator (copy + 3 == test.end())                                                                                      |
|  PASS  | 217: Copy Operator (*++copy == 'b')                                                                                              |
|  PASS  | 218: Copy Operator (*++copy == 'c')                                                                                              |
|  PASS  | 219: Copy Operator (++copy == test.end())                                                                                        |
|  PASS  | 221: Copy Operator (*copy++ == 'a')                                                                                              |
|  PASS  | 222: Copy Operator (*copy++ == 'b')                                                                                              |
|  PASS  | 223: Copy Operator (*copy++ == 'c')                                                                                              |
|  PASS  | 224: Copy Operator (copy == test.end())                                                                                          |
|  PASS  | 232: Move Operator (*copy == 'a')                                                                                                |
|  PASS  | 233: Move Operator (*(copy + 1) == 'b')                                                                                          |
|  PASS  | 234: Move Operator (*(copy + 2) == 'c')                                                                                          |
|  PASS  | 235: Move Operator (copy + 3 == test.end())                                                                                      |
|  PASS  | 236: Move Operator (*++copy == 'b')                                                                                              |
|  PASS  | 237: Move Operator (*++copy == 'c')                                                                                              |
|  PASS  | 238: Move Operator (++copy == test.end())                                                                                        |
|  PASS  | 241: Move Operator (*copy++ == 'a')                                                                                              |
|  PASS  | 242: Move Operator (*copy++ == 'b')                                                                                              |
|  PASS  | 243: Move Operator (*copy++ == 'c')                                                                                              |
|  PASS  | 244: Move Operator (copy == test.end())                                                                                          |
|  PASS  | 251: Dereference Operator (*it == 'a')                                                                                           |
|  PASS  | 252: Dereference Operator (*(it + 1) == 'b')                                                                                     |
|  PASS  | 253: Dereference Operator (*(it + 2) == 'c')                                                                                     |
|  PASS  | 254: Dereference Operator (it + 3 == test.end())                                                                                 |
|  PASS  | 255: Dereference Operator (*++it == 'b')                                                                                         |
|  PASS  | 256: Dereference Operator (*++it == 'c')                                                                                         |
|  PASS  | 257: Dereference Operator (++it == test.end())                                                                                   |
|  PASS  | 259: Dereference Operator (*it++ == 'a')                                                                                         |
|  PASS  | 260: Dereference Operator (*it++ == 'b')                                                                                         |
|  PASS  | 261: Dereference Operator (*it++ == 'c')                                                                                         |
|  PASS  | 262: Dereference Operator (it == test.end())                                                                                     |
|  PASS  | 269: Increment Operator (*it == 'a')                                                                                             |
|  PASS  | 270: Increment Operator (*(it + 1) == 'b')                                                                                       |
|  PASS  | 271: Increment Operator (*(it + 2) == 'c')                                                                                       |
|  PASS  | 272: Increment Operator (it + 3 == test.end())                                                                                   |
|  PASS  | 273: Increment Operator (*++it == 'b')                                                                                           |
|  PASS  | 274: Increment Operator (*++it == 'c')                                                                                           |
|  PASS  | 275: Increment Operator (++it == test.end())                                                                                     |
|  PASS  | 277: Increment Operator (*it++ == 'a')                                                                                           |
|  PASS  | 278: Increment Operator (*it++ == 'b')                                                                                           |
|  PASS  | 279: Increment Operator (*it++ == 'c')                                                                                           |
|  PASS  | 280: Increment Operator (it == test.end())                                                                                       |
|  PASS  | 287: Addition Operator (*it == 'a')                                                                                              |
|  PASS  | 288: Addition Operator (*(it + 1) == 'b')                                                                                        |
|  PASS  | 289: Addition Operator (*(it + 2) == 'c')                                                                                        |
|  PASS  | 290: Addition Operator (it + 3 == test.end())                                                                                    |
|  PASS  | 291: Addition Operator (*++it == 'b')                                                                                            |
|  PASS  | 292: Addition Operator (*++it == 'c')                                                                                            |
|  PASS  | 293: Addition Operator (++it == test.end())                                                                                      |
|  PASS  | 295: Addition Operator (*it++ == 'a')                                                                                            |
|  PASS  | 296: Addition Operator (*it++ == 'b')                                                                                            |
|  PASS  | 297: Addition Operator (*it++ == 'c')                                                                                            |
|  PASS  | 298: Addition Operator (it == test.end())                                                                                        |
|  PASS  | 306: Equal Operator (it == copy)                                                                                                 |
|  PASS  | 307: Equal Operator (copy == it)                                                                                                 |
|  PASS  | 308: Equal Operator (it == test.begin())                                                                                         |
|  PASS  | 309: Equal Operator (test.begin() == it)                                                                                         |
|  PASS  | 310: Equal Operator (copy == test.begin())                                                                                       |
|  PASS  | 311: Equal Operator (test.begin() == copy)                                                                                       |
|  PASS  | 319: Not Equal Operator (!(it != copy))                                                                                          |
|  PASS  | 320: Not Equal Operator (!(copy != it))                                                                                          |
|  PASS  | 321: Not Equal Operator (!(it != test.begin()))                                                                                  |
|  PASS  | 322: Not Equal Operator (!(test.begin() != it))                                                                                  |
|  PASS  | 323: Not Equal Operator (!(copy != test.begin()))                                                                                |
|  PASS  | 324: Not Equal Operator (!(test.begin() != copy))                                                                                |

## String
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 333: Default Constructor (test.get_capacity() == 0)                                                                              |
|  PASS  | 334: Default Constructor (test.get_size() == 0)                                                                                  |
|  PASS  | 335: Default Constructor (test.get_data() == nullptr)                                                                            |
|  PASS  | 341: Capacity Constructor (test.get_capacity() == 10)                                                                            |
|  PASS  | 342: Capacity Constructor (test.get_size() == 0)                                                                                 |
|  PASS  | 343: Capacity Constructor (test.get_data() != nullptr)                                                                           |
|  PASS  | 350: C String Constructor (test.get_capacity() == 13)                                                                            |
|  PASS  | 351: C String Constructor (test.get_size() == 13)                                                                                |
|  PASS  | 352: C String Constructor (test.get_data() != nullptr)                                                                           |
|  PASS  | 353: C String Constructor (test.get_data()[test.get_size()] == '\0')                                                             |
|  PASS  | 360: Character Constructor (test.get_capacity() == 3)                                                                            |
|  PASS  | 361: Character Constructor (test.get_size() == 3)                                                                                |
|  PASS  | 362: Character Constructor (test.get_data() != nullptr)                                                                          |
|  PASS  | 363: Character Constructor (test.get_data()[0] == 'a')                                                                           |
|  PASS  | 364: Character Constructor (test.get_data()[1] == 'a')                                                                           |
|  PASS  | 365: Character Constructor (test.get_data()[2] == 'a')                                                                           |
|  PASS  | 366: Character Constructor (test.get_data()[test.get_size()] == '\0')                                                            |
|  PASS  | 373: Copy Constructor (copy.get_capacity() == test.get_capacity())                                                               |
|  PASS  | 374: Copy Constructor (copy.get_size() == test.get_size())                                                                       |
|  PASS  | 375: Copy Constructor (copy.get_data() != nullptr)                                                                               |
|  PASS  | 382: Move Constructor (test.get_capacity() == 0)                                                                                 |
|  PASS  | 383: Move Constructor (test.get_size() == 0)                                                                                     |
|  PASS  | 384: Move Constructor (test.get_data() == nullptr)                                                                               |
|  PASS  | 385: Move Constructor (copy.get_capacity() == 13)                                                                                |
|  PASS  | 386: Move Constructor (copy.get_size() == 13)                                                                                    |
|  PASS  | 387: Move Constructor (copy.get_data() != nullptr)                                                                               |
|  PASS  | 394: Copy Operator (copy.get_capacity() == test.get_capacity())                                                                  |
|  PASS  | 395: Copy Operator (copy.get_size() == test.get_size())                                                                          |
|  PASS  | 396: Copy Operator (copy.get_data() != nullptr)                                                                                  |
|  PASS  | 403: Move Operator (test.get_capacity() == 0)                                                                                    |
|  PASS  | 404: Move Operator (test.get_size() == 0)                                                                                        |
|  PASS  | 405: Move Operator (test.get_data() == nullptr)                                                                                  |
|  PASS  | 406: Move Operator (copy.get_capacity() == 13)                                                                                   |
|  PASS  | 407: Move Operator (copy.get_size() == 13)                                                                                       |
|  PASS  | 408: Move Operator (copy.get_data() != nullptr)                                                                                  |
|  PASS  | 414: Index Operator (test[0] == 'H')                                                                                             |
|  PASS  | 415: Index Operator (test[1] == 'e')                                                                                             |
|  PASS  | 416: Index Operator (test[2] == 'l')                                                                                             |
|  PASS  | 417: Index Operator (test[3] == 'l')                                                                                             |
|  PASS  | 418: Index Operator (test[4] == 'o')                                                                                             |
|  PASS  | 419: Index Operator (test[5] == ' ')                                                                                             |
|  PASS  | 420: Index Operator (test[6] == 'w')                                                                                             |
|  PASS  | 421: Index Operator (test[7] == 'o')                                                                                             |
|  PASS  | 422: Index Operator (test[8] == 'r')                                                                                             |
|  PASS  | 423: Index Operator (test[9] == 'l')                                                                                             |
|  PASS  | 424: Index Operator (test[10] == 'd')                                                                                            |
|  PASS  | 425: Index Operator (test[11] == '!')                                                                                            |
|  PASS  | 426: Index Operator (test[12] == '\n')                                                                                           |
|  PASS  | 427: Index Operator (test[13])                                                                                                   |
|  PASS  | 434: Equal Operator (test == copy)                                                                                               |
|  PASS  | 437: Equal Operator (!(test == copy))                                                                                            |
|  PASS  | 440: Equal Operator (test == copy)                                                                                               |
|  PASS  | 443: Equal Operator (!(test == copy))                                                                                            |
|  PASS  | 450: Not Equal Operator (!(test != copy))                                                                                        |
|  PASS  | 453: Not Equal Operator (test != copy)                                                                                           |
|  PASS  | 456: Not Equal Operator (!(test != copy))                                                                                        |
|  PASS  | 459: Not Equal Operator (test != copy)                                                                                           |
|  PASS  | 466: Less Than Operator (!(test < copy))                                                                                         |
|  PASS  | 469: Less Than Operator (test < copy)                                                                                            |
|  PASS  | 472: Less Than Operator (!(test < copy))                                                                                         |
|  PASS  | 475: Less Than Operator (test < copy)                                                                                            |
|  PASS  | 478: Less Than Operator (!(test < copy))                                                                                         |
|  PASS  | 485: Less Than Or Equal Operator (test <= copy)                                                                                  |
|  PASS  | 488: Less Than Or Equal Operator (test <= copy)                                                                                  |
|  PASS  | 491: Less Than Or Equal Operator (test <= copy)                                                                                  |
|  PASS  | 494: Less Than Or Equal Operator (test <= copy)                                                                                  |
|  PASS  | 497: Less Than Or Equal Operator (!(test <= copy))                                                                               |
|  PASS  | 504: Greater Than Operator (!(test > copy))                                                                                      |
|  PASS  | 507: Greater Than Operator (!(test > copy))                                                                                      |
|  PASS  | 510: Greater Than Operator (!(test > copy))                                                                                      |
|  PASS  | 513: Greater Than Operator (!(test > copy))                                                                                      |
|  PASS  | 516: Greater Than Operator (test > copy)                                                                                         |
|  PASS  | 519: Greater Than Operator (!(test > copy))                                                                                      |
|  PASS  | 526: Greater Than Or Equal Operator (test >= copy)                                                                               |
|  PASS  | 529: Greater Than Or Equal Operator (!(test >= copy))                                                                            |
|  PASS  | 532: Greater Than Or Equal Operator (test >= copy)                                                                               |
|  PASS  | 535: Greater Than Or Equal Operator (!(test >= copy))                                                                            |
|  PASS  | 538: Greater Than Or Equal Operator (test >= copy)                                                                               |
|  PASS  | 541: Greater Than Or Equal Operator (!(test >= copy))                                                                            |
|  PASS  | 549: Addition Operator (result == "Hello world!\n")                                                                              |
|  PASS  | 553: Addition Operator (result == "Hello ")                                                                                      |
|  PASS  | 557: Addition Operator (result == "")                                                                                            |
|  PASS  | 566: Stream Insertion Operator (stream.str() == "Hello world!\n")                                                                |
|  PASS  | 572: Stream Insertion Operator (stream.str() == "")                                                                              |
|  PASS  | 580: Get Capacity (test.get_capacity() == 100)                                                                                   |
|  PASS  | 587: Get Size (test.get_size() == 13)                                                                                            |
|  PASS  | 594: Get Data (test.get_data() != nullptr)                                                                                       |
|  PASS  | 602: Reserve (test.get_capacity() == 0)                                                                                          |
|  PASS  | 605: Reserve (test.get_capacity() == 100)                                                                                        |
|  PASS  | 608: Reserve (test.get_capacity() == 10)                                                                                         |
|  PASS  | 616: Resize (test.get_size() == 0)                                                                                               |
|  PASS  | 617: Resize (test.get_capacity() == 0)                                                                                           |
|  PASS  | 620: Resize (test.get_size() == 100)                                                                                             |
|  PASS  | 621: Resize (test.get_capacity() == 100)                                                                                         |
|  PASS  | 624: Resize (test.get_size() == 10)                                                                                              |
|  PASS  | 625: Resize (test.get_capacity() == 100)                                                                                         |
|  PASS  | 631: Is Empty (test.is_empty())                                                                                                  |
|  PASS  | 634: Is Empty (!test.is_empty())                                                                                                 |
|  PASS  | 640: At (test.at(0) == 'H')                                                                                                      |
|  PASS  | 641: At (test.at(1) == 'e')                                                                                                      |
|  PASS  | 642: At (test.at(2) == 'l')                                                                                                      |
|  PASS  | 643: At (test.at(3) == 'l')                                                                                                      |
|  PASS  | 644: At (test.at(4) == 'o')                                                                                                      |
|  PASS  | 645: At (test.at(5) == ' ')                                                                                                      |
|  PASS  | 646: At (test.at(6) == 'w')                                                                                                      |
|  PASS  | 647: At (test.at(7) == 'o')                                                                                                      |
|  PASS  | 648: At (test.at(8) == 'r')                                                                                                      |
|  PASS  | 649: At (test.at(9) == 'l')                                                                                                      |
|  PASS  | 650: At (test.at(10) == 'd')                                                                                                     |
|  PASS  | 651: At (test.at(11) == '!')                                                                                                     |
|  PASS  | 652: At (test.at(12) == '\n')                                                                                                    |
|  PASS  | 653: At (test.at(13))                                                                                                            |
|  PASS  | 659: Sub (test.sub(0, 5) == "Hello")                                                                                             |
|  PASS  | 660: Sub (test.sub(6, 5) == "world")                                                                                             |
|  PASS  | 661: Sub (test.sub(12, 1) == "\n")                                                                                               |
|  PASS  | 662: Sub (test.sub(13, 1))                                                                                                       |
|  PASS  | 668: Find (test.find("Hello") == 0)                                                                                              |
|  PASS  | 669: Find (test.find("world") == 6)                                                                                              |
|  PASS  | 670: Find (test.find("\n") == 12)                                                                                                |
|  PASS  | 671: Find (test.find("Hello world!\n") == 0)                                                                                     |
|  PASS  | 672: Find (test.find("aaa") == INVALID_INDEX)                                                                                    |
|  PASS  | 673: Find (test.find("") == INVALID_INDEX)                                                                                       |
|  PASS  | 676: Find (test.find("aaa") == INVALID_INDEX)                                                                                    |
|  PASS  | 682: Contains (test.contains("Hello"))                                                                                           |
|  PASS  | 683: Contains (test.contains("world"))                                                                                           |
|  PASS  | 684: Contains (test.contains("\n"))                                                                                              |
|  PASS  | 685: Contains (test.contains("Hello world!\n"))                                                                                  |
|  PASS  | 686: Contains (!test.contains("aaa"))                                                                                            |
|  PASS  | 687: Contains (!test.contains(""))                                                                                               |
|  PASS  | 690: Contains (!test.contains("aaa"))                                                                                            |
|  PASS  | 697: Begin/End (*it == 'a')                                                                                                      |
|  PASS  | 698: Begin/End (*(it + 1) == 'b')                                                                                                |
|  PASS  | 699: Begin/End (*(it + 2) == 'c')                                                                                                |
|  PASS  | 700: Begin/End (it + 3 == test.end())                                                                                            |
|  PASS  | 701: Begin/End (*++it == 'b')                                                                                                    |
|  PASS  | 702: Begin/End (*++it == 'c')                                                                                                    |
|  PASS  | 703: Begin/End (++it == test.end())                                                                                              |
|  PASS  | 705: Begin/End (*it++ == 'a')                                                                                                    |
|  PASS  | 706: Begin/End (*it++ == 'b')                                                                                                    |
|  PASS  | 707: Begin/End (*it++ == 'c')                                                                                                    |
|  PASS  | 708: Begin/End (it == test.end())                                                                                                |
|  PASS  | 715: Const Begin/End (*it == 'a')                                                                                                |
|  PASS  | 716: Const Begin/End (*(it + 1) == 'b')                                                                                          |
|  PASS  | 717: Const Begin/End (*(it + 2) == 'c')                                                                                          |
|  PASS  | 718: Const Begin/End (it + 3 == test.end())                                                                                      |
|  PASS  | 719: Const Begin/End (*++it == 'b')                                                                                              |
|  PASS  | 720: Const Begin/End (*++it == 'c')                                                                                              |
|  PASS  | 721: Const Begin/End (++it == test.end())                                                                                        |
|  PASS  | 723: Const Begin/End (*it++ == 'a')                                                                                              |
|  PASS  | 724: Const Begin/End (*it++ == 'b')                                                                                              |
|  PASS  | 725: Const Begin/End (*it++ == 'c')                                                                                              |
|  PASS  | 726: Const Begin/End (it == test.end())                                                                                          |

## Vector::Iterator
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 13: Copy Constructor (*copy == 5)                                                                                                |
|  PASS  | 14: Copy Constructor (*(copy + 1) == 5)                                                                                          |
|  PASS  | 15: Copy Constructor (*(copy + 2) == 5)                                                                                          |
|  PASS  | 16: Copy Constructor (copy + 3 == test.end())                                                                                    |
|  PASS  | 17: Copy Constructor (*++copy == 5)                                                                                              |
|  PASS  | 18: Copy Constructor (*++copy == 5)                                                                                              |
|  PASS  | 19: Copy Constructor (++copy == test.end())                                                                                      |
|  PASS  | 21: Copy Constructor (*copy++ == 5)                                                                                              |
|  PASS  | 22: Copy Constructor (*copy++ == 5)                                                                                              |
|  PASS  | 23: Copy Constructor (*copy++ == 5)                                                                                              |
|  PASS  | 24: Copy Constructor (copy == test.end())                                                                                        |
|  PASS  | 32: Move Constructor (*copy == 5)                                                                                                |
|  PASS  | 33: Move Constructor (*(copy + 1) == 5)                                                                                          |
|  PASS  | 34: Move Constructor (*(copy + 2) == 5)                                                                                          |
|  PASS  | 35: Move Constructor (copy + 3 == test.end())                                                                                    |
|  PASS  | 36: Move Constructor (*++copy == 5)                                                                                              |
|  PASS  | 37: Move Constructor (*++copy == 5)                                                                                              |
|  PASS  | 38: Move Constructor (++copy == test.end())                                                                                      |
|  PASS  | 41: Move Constructor (*copy++ == 5)                                                                                              |
|  PASS  | 42: Move Constructor (*copy++ == 5)                                                                                              |
|  PASS  | 43: Move Constructor (*copy++ == 5)                                                                                              |
|  PASS  | 44: Move Constructor (copy == test.end())                                                                                        |
|  PASS  | 52: Copy Operator (*copy == 5)                                                                                                   |
|  PASS  | 53: Copy Operator (*(copy + 1) == 5)                                                                                             |
|  PASS  | 54: Copy Operator (*(copy + 2) == 5)                                                                                             |
|  PASS  | 55: Copy Operator (copy + 3 == test.end())                                                                                       |
|  PASS  | 56: Copy Operator (*++copy == 5)                                                                                                 |
|  PASS  | 57: Copy Operator (*++copy == 5)                                                                                                 |
|  PASS  | 58: Copy Operator (++copy == test.end())                                                                                         |
|  PASS  | 60: Copy Operator (*copy++ == 5)                                                                                                 |
|  PASS  | 61: Copy Operator (*copy++ == 5)                                                                                                 |
|  PASS  | 62: Copy Operator (*copy++ == 5)                                                                                                 |
|  PASS  | 63: Copy Operator (copy == test.end())                                                                                           |
|  PASS  | 71: Move Operator (*copy == 5)                                                                                                   |
|  PASS  | 72: Move Operator (*(copy + 1) == 5)                                                                                             |
|  PASS  | 73: Move Operator (*(copy + 2) == 5)                                                                                             |
|  PASS  | 74: Move Operator (copy + 3 == test.end())                                                                                       |
|  PASS  | 75: Move Operator (*++copy == 5)                                                                                                 |
|  PASS  | 76: Move Operator (*++copy == 5)                                                                                                 |
|  PASS  | 77: Move Operator (++copy == test.end())                                                                                         |
|  PASS  | 80: Move Operator (*copy++ == 5)                                                                                                 |
|  PASS  | 81: Move Operator (*copy++ == 5)                                                                                                 |
|  PASS  | 82: Move Operator (*copy++ == 5)                                                                                                 |
|  PASS  | 83: Move Operator (copy == test.end())                                                                                           |
|  PASS  | 90: Dereference Operator (*it == 5)                                                                                              |
|  PASS  | 91: Dereference Operator (*(it + 1) == 5)                                                                                        |
|  PASS  | 92: Dereference Operator (*(it + 2) == 5)                                                                                        |
|  PASS  | 99: Increment Operator (*it == 5)                                                                                                |
|  PASS  | 100: Increment Operator (*(it + 1) == 5)                                                                                         |
|  PASS  | 101: Increment Operator (*(it + 2) == 5)                                                                                         |
|  PASS  | 102: Increment Operator (it + 3 == test.end())                                                                                   |
|  PASS  | 103: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 104: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 105: Increment Operator (++it == test.end())                                                                                     |
|  PASS  | 107: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 108: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 109: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 110: Increment Operator (it == test.end())                                                                                       |
|  PASS  | 117: Decrement Operator (*(it - 1) == 5)                                                                                         |
|  PASS  | 118: Decrement Operator (*(it - 2) == 5)                                                                                         |
|  PASS  | 119: Decrement Operator (it - 3 == test.begin())                                                                                 |
|  PASS  | 120: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 121: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 122: Decrement Operator (--it == test.begin())                                                                                   |
|  PASS  | 125: Decrement Operator (*it-- == 5)                                                                                             |
|  PASS  | 126: Decrement Operator (*it-- == 5)                                                                                             |
|  PASS  | 127: Decrement Operator (it == test.begin())                                                                                     |
|  PASS  | 134: Addition Operator (*it == 5)                                                                                                |
|  PASS  | 135: Addition Operator (*(it + 1) == 5)                                                                                          |
|  PASS  | 136: Addition Operator (*(it + 2) == 5)                                                                                          |
|  PASS  | 143: Subtraction Operator (it - 3 == test.begin())                                                                               |
|  PASS  | 144: Subtraction Operator (it - 2 == test.begin() + 1)                                                                           |
|  PASS  | 145: Subtraction Operator (it - 1 == test.begin() + 2)                                                                           |
|  PASS  | 153: Equal Operator (it == copy)                                                                                                 |
|  PASS  | 154: Equal Operator (copy == it)                                                                                                 |
|  PASS  | 155: Equal Operator (it == test.begin())                                                                                         |
|  PASS  | 156: Equal Operator (test.begin() == it)                                                                                         |
|  PASS  | 157: Equal Operator (copy == test.begin())                                                                                       |
|  PASS  | 158: Equal Operator (test.begin() == copy)                                                                                       |
|  PASS  | 166: Not Equal Operator (!(it != copy))                                                                                          |
|  PASS  | 167: Not Equal Operator (!(copy != it))                                                                                          |
|  PASS  | 168: Not Equal Operator (!(it != test.begin()))                                                                                  |
|  PASS  | 169: Not Equal Operator (!(test.begin() != it))                                                                                  |
|  PASS  | 170: Not Equal Operator (!(copy != test.begin()))                                                                                |
|  PASS  | 171: Not Equal Operator (!(test.begin() != copy))                                                                                |

## Vector::ConstIterator
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 182: Copy Constructor (*copy == 5)                                                                                               |
|  PASS  | 183: Copy Constructor (*(copy + 1) == 5)                                                                                         |
|  PASS  | 184: Copy Constructor (*(copy + 2) == 5)                                                                                         |
|  PASS  | 185: Copy Constructor (copy + 3 == test.end())                                                                                   |
|  PASS  | 186: Copy Constructor (*++copy == 5)                                                                                             |
|  PASS  | 187: Copy Constructor (*++copy == 5)                                                                                             |
|  PASS  | 188: Copy Constructor (++copy == test.end())                                                                                     |
|  PASS  | 190: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 191: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 192: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 193: Copy Constructor (copy == test.end())                                                                                       |
|  PASS  | 201: Move Constructor (*copy == 5)                                                                                               |
|  PASS  | 202: Move Constructor (*(copy + 1) == 5)                                                                                         |
|  PASS  | 203: Move Constructor (*(copy + 2) == 5)                                                                                         |
|  PASS  | 204: Move Constructor (copy + 3 == test.end())                                                                                   |
|  PASS  | 205: Move Constructor (*++copy == 5)                                                                                             |
|  PASS  | 206: Move Constructor (*++copy == 5)                                                                                             |
|  PASS  | 207: Move Constructor (++copy == test.end())                                                                                     |
|  PASS  | 210: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 211: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 212: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 213: Move Constructor (copy == test.end())                                                                                       |
|  PASS  | 221: Copy Operator (*copy == 5)                                                                                                  |
|  PASS  | 222: Copy Operator (*(copy + 1) == 5)                                                                                            |
|  PASS  | 223: Copy Operator (*(copy + 2) == 5)                                                                                            |
|  PASS  | 224: Copy Operator (copy + 3 == test.end())                                                                                      |
|  PASS  | 225: Copy Operator (*++copy == 5)                                                                                                |
|  PASS  | 226: Copy Operator (*++copy == 5)                                                                                                |
|  PASS  | 227: Copy Operator (++copy == test.end())                                                                                        |
|  PASS  | 229: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 230: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 231: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 232: Copy Operator (copy == test.end())                                                                                          |
|  PASS  | 240: Move Operator (*copy == 5)                                                                                                  |
|  PASS  | 241: Move Operator (*(copy + 1) == 5)                                                                                            |
|  PASS  | 242: Move Operator (*(copy + 2) == 5)                                                                                            |
|  PASS  | 243: Move Operator (copy + 3 == test.end())                                                                                      |
|  PASS  | 244: Move Operator (*++copy == 5)                                                                                                |
|  PASS  | 245: Move Operator (*++copy == 5)                                                                                                |
|  PASS  | 246: Move Operator (++copy == test.end())                                                                                        |
|  PASS  | 249: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 250: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 251: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 252: Move Operator (copy == test.end())                                                                                          |
|  PASS  | 259: Dereference Operator (*it == 5)                                                                                             |
|  PASS  | 260: Dereference Operator (*(it + 1) == 5)                                                                                       |
|  PASS  | 261: Dereference Operator (*(it + 2) == 5)                                                                                       |
|  PASS  | 268: Increment Operator (*it == 5)                                                                                               |
|  PASS  | 269: Increment Operator (*(it + 1) == 5)                                                                                         |
|  PASS  | 270: Increment Operator (*(it + 2) == 5)                                                                                         |
|  PASS  | 271: Increment Operator (it + 3 == test.end())                                                                                   |
|  PASS  | 272: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 273: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 274: Increment Operator (++it == test.end())                                                                                     |
|  PASS  | 276: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 277: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 278: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 279: Increment Operator (it == test.end())                                                                                       |
|  PASS  | 286: Decrement Operator (*(it - 1) == 5)                                                                                         |
|  PASS  | 287: Decrement Operator (*(it - 2) == 5)                                                                                         |
|  PASS  | 288: Decrement Operator (it - 3 == test.begin())                                                                                 |
|  PASS  | 289: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 290: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 291: Decrement Operator (--it == test.begin())                                                                                   |
|  PASS  | 294: Decrement Operator (*it-- == 5)                                                                                             |
|  PASS  | 295: Decrement Operator (*it-- == 5)                                                                                             |
|  PASS  | 296: Decrement Operator (it == test.begin())                                                                                     |
|  PASS  | 303: Addition Operator (*it == 5)                                                                                                |
|  PASS  | 304: Addition Operator (*(it + 1) == 5)                                                                                          |
|  PASS  | 305: Addition Operator (*(it + 2) == 5)                                                                                          |
|  PASS  | 312: Subtraction Operator (it - 3 == test.begin())                                                                               |
|  PASS  | 313: Subtraction Operator (it - 2 == test.begin() + 1)                                                                           |
|  PASS  | 314: Subtraction Operator (it - 1 == test.begin() + 2)                                                                           |
|  PASS  | 322: Equal Operator (it == copy)                                                                                                 |
|  PASS  | 323: Equal Operator (copy == it)                                                                                                 |
|  PASS  | 324: Equal Operator (it == test.begin())                                                                                         |
|  PASS  | 325: Equal Operator (test.begin() == it)                                                                                         |
|  PASS  | 326: Equal Operator (copy == test.begin())                                                                                       |
|  PASS  | 327: Equal Operator (test.begin() == copy)                                                                                       |
|  PASS  | 335: Not Equal Operator (!(it != copy))                                                                                          |
|  PASS  | 336: Not Equal Operator (!(copy != it))                                                                                          |
|  PASS  | 337: Not Equal Operator (!(it != test.begin()))                                                                                  |
|  PASS  | 338: Not Equal Operator (!(test.begin() != it))                                                                                  |
|  PASS  | 339: Not Equal Operator (!(copy != test.begin()))                                                                                |
|  PASS  | 340: Not Equal Operator (!(test.begin() != copy))                                                                                |

## Vector::ReverseIterator
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 351: Copy Constructor (*copy == 5)                                                                                               |
|  PASS  | 352: Copy Constructor (*(copy + 1) == 5)                                                                                         |
|  PASS  | 353: Copy Constructor (*(copy + 2) == 5)                                                                                         |
|  PASS  | 354: Copy Constructor (copy + 3 == test.rend())                                                                                  |
|  PASS  | 355: Copy Constructor (*++copy == 5)                                                                                             |
|  PASS  | 356: Copy Constructor (*++copy == 5)                                                                                             |
|  PASS  | 357: Copy Constructor (++copy == test.rend())                                                                                    |
|  PASS  | 359: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 360: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 361: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 362: Copy Constructor (copy == test.rend())                                                                                      |
|  PASS  | 370: Move Constructor (*copy == 5)                                                                                               |
|  PASS  | 371: Move Constructor (*(copy + 1) == 5)                                                                                         |
|  PASS  | 372: Move Constructor (*(copy + 2) == 5)                                                                                         |
|  PASS  | 373: Move Constructor (copy + 3 == test.rend())                                                                                  |
|  PASS  | 374: Move Constructor (*++copy == 5)                                                                                             |
|  PASS  | 375: Move Constructor (*++copy == 5)                                                                                             |
|  PASS  | 376: Move Constructor (++copy == test.rend())                                                                                    |
|  PASS  | 379: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 380: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 381: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 382: Move Constructor (copy == test.rend())                                                                                      |
|  PASS  | 390: Copy Operator (*copy == 5)                                                                                                  |
|  PASS  | 391: Copy Operator (*(copy + 1) == 5)                                                                                            |
|  PASS  | 392: Copy Operator (*(copy + 2) == 5)                                                                                            |
|  PASS  | 393: Copy Operator (copy + 3 == test.rend())                                                                                     |
|  PASS  | 394: Copy Operator (*++copy == 5)                                                                                                |
|  PASS  | 395: Copy Operator (*++copy == 5)                                                                                                |
|  PASS  | 396: Copy Operator (++copy == test.rend())                                                                                       |
|  PASS  | 398: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 399: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 400: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 401: Copy Operator (copy == test.rend())                                                                                         |
|  PASS  | 409: Move Operator (*copy == 5)                                                                                                  |
|  PASS  | 410: Move Operator (*(copy + 1) == 5)                                                                                            |
|  PASS  | 411: Move Operator (*(copy + 2) == 5)                                                                                            |
|  PASS  | 412: Move Operator (copy + 3 == test.rend())                                                                                     |
|  PASS  | 413: Move Operator (*++copy == 5)                                                                                                |
|  PASS  | 414: Move Operator (*++copy == 5)                                                                                                |
|  PASS  | 415: Move Operator (++copy == test.rend())                                                                                       |
|  PASS  | 418: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 419: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 420: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 421: Move Operator (copy == test.rend())                                                                                         |
|  PASS  | 428: Dereference Operator (*it == 5)                                                                                             |
|  PASS  | 429: Dereference Operator (*(it + 1) == 5)                                                                                       |
|  PASS  | 430: Dereference Operator (*(it + 2) == 5)                                                                                       |
|  PASS  | 437: Increment Operator (*it == 5)                                                                                               |
|  PASS  | 438: Increment Operator (*(it + 1) == 5)                                                                                         |
|  PASS  | 439: Increment Operator (*(it + 2) == 5)                                                                                         |
|  PASS  | 440: Increment Operator (it + 3 == test.rend())                                                                                  |
|  PASS  | 441: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 442: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 443: Increment Operator (++it == test.rend())                                                                                    |
|  PASS  | 445: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 446: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 447: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 448: Increment Operator (it == test.rend())                                                                                      |
|  PASS  | 455: Decrement Operator (*(it - 1) == 5)                                                                                         |
|  PASS  | 456: Decrement Operator (*(it - 2) == 5)                                                                                         |
|  PASS  | 457: Decrement Operator (it - 3 == test.rbegin())                                                                                |
|  PASS  | 458: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 459: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 460: Decrement Operator (--it == test.rbegin())                                                                                  |
|  PASS  | 463: Decrement Operator (*it-- == 5)                                                                                             |
|  PASS  | 464: Decrement Operator (*it-- == 5)                                                                                             |
|  PASS  | 465: Decrement Operator (it == test.rbegin())                                                                                    |
|  PASS  | 472: Addition Operator (*it == 5)                                                                                                |
|  PASS  | 473: Addition Operator (*(it + 1) == 5)                                                                                          |
|  PASS  | 474: Addition Operator (*(it + 2) == 5)                                                                                          |
|  PASS  | 481: Subtraction Operator (it - 3 == test.rbegin())                                                                              |
|  PASS  | 482: Subtraction Operator (it - 2 == test.rbegin() + 1)                                                                          |
|  PASS  | 483: Subtraction Operator (it - 1 == test.rbegin() + 2)                                                                          |
|  PASS  | 491: Equal Operator (it == copy)                                                                                                 |
|  PASS  | 492: Equal Operator (copy == it)                                                                                                 |
|  PASS  | 493: Equal Operator (it == test.rbegin())                                                                                        |
|  PASS  | 494: Equal Operator (test.rbegin() == it)                                                                                        |
|  PASS  | 495: Equal Operator (copy == test.rbegin())                                                                                      |
|  PASS  | 496: Equal Operator (test.rbegin() == copy)                                                                                      |
|  PASS  | 504: Not Equal Operator (!(it != copy))                                                                                          |
|  PASS  | 505: Not Equal Operator (!(copy != it))                                                                                          |
|  PASS  | 506: Not Equal Operator (!(it != test.rbegin()))                                                                                 |
|  PASS  | 507: Not Equal Operator (!(test.rbegin() != it))                                                                                 |
|  PASS  | 508: Not Equal Operator (!(copy != test.rbegin()))                                                                               |
|  PASS  | 509: Not Equal Operator (!(test.rbegin() != copy))                                                                               |

## Vector::ConstReverseIterator
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 520: Copy Constructor (*copy == 5)                                                                                               |
|  PASS  | 521: Copy Constructor (*(copy + 1) == 5)                                                                                         |
|  PASS  | 522: Copy Constructor (*(copy + 2) == 5)                                                                                         |
|  PASS  | 523: Copy Constructor (copy + 3 == test.rend())                                                                                  |
|  PASS  | 524: Copy Constructor (*++copy == 5)                                                                                             |
|  PASS  | 525: Copy Constructor (*++copy == 5)                                                                                             |
|  PASS  | 526: Copy Constructor (++copy == test.rend())                                                                                    |
|  PASS  | 528: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 529: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 530: Copy Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 531: Copy Constructor (copy == test.rend())                                                                                      |
|  PASS  | 539: Move Constructor (*copy == 5)                                                                                               |
|  PASS  | 540: Move Constructor (*(copy + 1) == 5)                                                                                         |
|  PASS  | 541: Move Constructor (*(copy + 2) == 5)                                                                                         |
|  PASS  | 542: Move Constructor (copy + 3 == test.rend())                                                                                  |
|  PASS  | 543: Move Constructor (*++copy == 5)                                                                                             |
|  PASS  | 544: Move Constructor (*++copy == 5)                                                                                             |
|  PASS  | 545: Move Constructor (++copy == test.rend())                                                                                    |
|  PASS  | 548: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 549: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 550: Move Constructor (*copy++ == 5)                                                                                             |
|  PASS  | 551: Move Constructor (copy == test.rend())                                                                                      |
|  PASS  | 559: Copy Operator (*copy == 5)                                                                                                  |
|  PASS  | 560: Copy Operator (*(copy + 1) == 5)                                                                                            |
|  PASS  | 561: Copy Operator (*(copy + 2) == 5)                                                                                            |
|  PASS  | 562: Copy Operator (copy + 3 == test.rend())                                                                                     |
|  PASS  | 563: Copy Operator (*++copy == 5)                                                                                                |
|  PASS  | 564: Copy Operator (*++copy == 5)                                                                                                |
|  PASS  | 565: Copy Operator (++copy == test.rend())                                                                                       |
|  PASS  | 567: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 568: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 569: Copy Operator (*copy++ == 5)                                                                                                |
|  PASS  | 570: Copy Operator (copy == test.rend())                                                                                         |
|  PASS  | 578: Move Operator (*copy == 5)                                                                                                  |
|  PASS  | 579: Move Operator (*(copy + 1) == 5)                                                                                            |
|  PASS  | 580: Move Operator (*(copy + 2) == 5)                                                                                            |
|  PASS  | 581: Move Operator (copy + 3 == test.rend())                                                                                     |
|  PASS  | 582: Move Operator (*++copy == 5)                                                                                                |
|  PASS  | 583: Move Operator (*++copy == 5)                                                                                                |
|  PASS  | 584: Move Operator (++copy == test.rend())                                                                                       |
|  PASS  | 587: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 588: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 589: Move Operator (*copy++ == 5)                                                                                                |
|  PASS  | 590: Move Operator (copy == test.rend())                                                                                         |
|  PASS  | 597: Dereference Operator (*it == 5)                                                                                             |
|  PASS  | 598: Dereference Operator (*(it + 1) == 5)                                                                                       |
|  PASS  | 599: Dereference Operator (*(it + 2) == 5)                                                                                       |
|  PASS  | 606: Increment Operator (*it == 5)                                                                                               |
|  PASS  | 607: Increment Operator (*(it + 1) == 5)                                                                                         |
|  PASS  | 608: Increment Operator (*(it + 2) == 5)                                                                                         |
|  PASS  | 609: Increment Operator (it + 3 == test.rend())                                                                                  |
|  PASS  | 610: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 611: Increment Operator (*++it == 5)                                                                                             |
|  PASS  | 612: Increment Operator (++it == test.rend())                                                                                    |
|  PASS  | 614: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 615: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 616: Increment Operator (*it++ == 5)                                                                                             |
|  PASS  | 617: Increment Operator (it == test.rend())                                                                                      |
|  PASS  | 624: Decrement Operator (*(it - 1) == 5)                                                                                         |
|  PASS  | 625: Decrement Operator (*(it - 2) == 5)                                                                                         |
|  PASS  | 626: Decrement Operator (it - 3 == test.rbegin())                                                                                |
|  PASS  | 627: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 628: Decrement Operator (*--it == 5)                                                                                             |
|  PASS  | 629: Decrement Operator (--it == test.rbegin())                                                                                  |
|  PASS  | 632: Decrement Operator (*it-- == 5)                                                                                             |
|  PASS  | 633: Decrement Operator (*it-- == 5)                                                                                             |
|  PASS  | 634: Decrement Operator (it == test.rbegin())                                                                                    |
|  PASS  | 641: Addition Operator (*it == 5)                                                                                                |
|  PASS  | 642: Addition Operator (*(it + 1) == 5)                                                                                          |
|  PASS  | 643: Addition Operator (*(it + 2) == 5)                                                                                          |
|  PASS  | 650: Subtraction Operator (it - 3 == test.rbegin())                                                                              |
|  PASS  | 651: Subtraction Operator (it - 2 == test.rbegin() + 1)                                                                          |
|  PASS  | 652: Subtraction Operator (it - 1 == test.rbegin() + 2)                                                                          |
|  PASS  | 660: Equal Operator (it == copy)                                                                                                 |
|  PASS  | 661: Equal Operator (copy == it)                                                                                                 |
|  PASS  | 662: Equal Operator (it == test.rbegin())                                                                                        |
|  PASS  | 663: Equal Operator (test.rbegin() == it)                                                                                        |
|  PASS  | 664: Equal Operator (copy == test.rbegin())                                                                                      |
|  PASS  | 665: Equal Operator (test.rbegin() == copy)                                                                                      |
|  PASS  | 673: Not Equal Operator (!(it != copy))                                                                                          |
|  PASS  | 674: Not Equal Operator (!(copy != it))                                                                                          |
|  PASS  | 675: Not Equal Operator (!(it != test.rbegin()))                                                                                 |
|  PASS  | 676: Not Equal Operator (!(test.rbegin() != it))                                                                                 |
|  PASS  | 677: Not Equal Operator (!(copy != test.rbegin()))                                                                               |
|  PASS  | 678: Not Equal Operator (!(test.rbegin() != copy))                                                                               |

## Vector
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 687: Default Constructor (vec.get_size() == 0)                                                                                   |
|  PASS  | 688: Default Constructor (vec.get_capacity() == 0)                                                                               |
|  PASS  | 689: Default Constructor (vec.get_data() == nullptr)                                                                             |
|  PASS  | 695: Capacity Constructor (vec.get_size() == 0)                                                                                  |
|  PASS  | 696: Capacity Constructor (vec.get_capacity() == 10)                                                                             |
|  PASS  | 697: Capacity Constructor (vec.get_data() != nullptr)                                                                            |
|  PASS  | 700: Capacity Constructor (vec2.get_size() == 0)                                                                                 |
|  PASS  | 701: Capacity Constructor (vec2.get_capacity() == 0)                                                                             |
|  PASS  | 702: Capacity Constructor (vec2.get_data() == nullptr)                                                                           |
|  PASS  | 708: Value Constructor (vec.get_size() == 10)                                                                                    |
|  PASS  | 709: Value Constructor (vec.get_capacity() == 10)                                                                                |
|  PASS  | 710: Value Constructor (vec.get_data() != nullptr)                                                                               |
|  PASS  | 713: Value Constructor (vec[i] == 5)                                                                                             |
|  PASS  | 713: Value Constructor (vec[i] == 5)                                                                                             |
|  PASS  | 713: Value Constructor (vec[i] == 5)                                                                                             |
|  PASS  | 713: Value Constructor (vec[i] == 5)                                                                                             |
|  PASS  | 713: Value Constructor (vec[i] == 5)                                                                                             |
|  PASS  | 713: Value Constructor (vec[i] == 5)                                                                                             |
|  PASS  | 713: Value Constructor (vec[i] == 5)                                                                                             |
|  PASS  | 713: Value Constructor (vec[i] == 5)                                                                                             |
|  PASS  | 713: Value Constructor (vec[i] == 5)                                                                                             |
|  PASS  | 713: Value Constructor (vec[i] == 5)                                                                                             |
|  PASS  | 717: Value Constructor (vec2.get_size() == 0)                                                                                    |
|  PASS  | 718: Value Constructor (vec2.get_capacity() == 0)                                                                                |
|  PASS  | 719: Value Constructor (vec2.get_data() == nullptr)                                                                              |
|  PASS  | 725: Initializer List Constructor (vec.get_size() == 5)                                                                          |
|  PASS  | 726: Initializer List Constructor (vec.get_capacity() == 5)                                                                      |
|  PASS  | 727: Initializer List Constructor (vec.get_data() != nullptr)                                                                    |
|  PASS  | 730: Initializer List Constructor (vec[i] == i)                                                                                  |
|  PASS  | 730: Initializer List Constructor (vec[i] == i)                                                                                  |
|  PASS  | 730: Initializer List Constructor (vec[i] == i)                                                                                  |
|  PASS  | 730: Initializer List Constructor (vec[i] == i)                                                                                  |
|  PASS  | 730: Initializer List Constructor (vec[i] == i)                                                                                  |
|  PASS  | 734: Initializer List Constructor (vec2.get_size() == 0)                                                                         |
|  PASS  | 735: Initializer List Constructor (vec2.get_capacity() == 0)                                                                     |
|  PASS  | 736: Initializer List Constructor (vec2.get_data() == nullptr)                                                                   |
|  PASS  | 743: Copy Constructor (copy.get_size() == 5)                                                                                     |
|  PASS  | 744: Copy Constructor (copy.get_capacity() == 5)                                                                                 |
|  PASS  | 745: Copy Constructor (copy.get_data() != nullptr)                                                                               |
|  PASS  | 748: Copy Constructor (copy[i] == i)                                                                                             |
|  PASS  | 748: Copy Constructor (copy[i] == i)                                                                                             |
|  PASS  | 748: Copy Constructor (copy[i] == i)                                                                                             |
|  PASS  | 748: Copy Constructor (copy[i] == i)                                                                                             |
|  PASS  | 748: Copy Constructor (copy[i] == i)                                                                                             |
|  PASS  | 756: Move Constructor (copy.get_size() == 5)                                                                                     |
|  PASS  | 757: Move Constructor (copy.get_capacity() == 5)                                                                                 |
|  PASS  | 758: Move Constructor (copy.get_data() != nullptr)                                                                               |
|  PASS  | 761: Move Constructor (copy[i] == i)                                                                                             |
|  PASS  | 761: Move Constructor (copy[i] == i)                                                                                             |
|  PASS  | 761: Move Constructor (copy[i] == i)                                                                                             |
|  PASS  | 761: Move Constructor (copy[i] == i)                                                                                             |
|  PASS  | 761: Move Constructor (copy[i] == i)                                                                                             |
|  PASS  | 769: Copy Operator (copy.get_size() == 5)                                                                                        |
|  PASS  | 770: Copy Operator (copy.get_capacity() == 5)                                                                                    |
|  PASS  | 771: Copy Operator (copy.get_data() != nullptr)                                                                                  |
|  PASS  | 774: Copy Operator (copy[i] == i)                                                                                                |
|  PASS  | 774: Copy Operator (copy[i] == i)                                                                                                |
|  PASS  | 774: Copy Operator (copy[i] == i)                                                                                                |
|  PASS  | 774: Copy Operator (copy[i] == i)                                                                                                |
|  PASS  | 774: Copy Operator (copy[i] == i)                                                                                                |
|  PASS  | 782: Move Operator (copy.get_size() == 5)                                                                                        |
|  PASS  | 783: Move Operator (copy.get_capacity() == 5)                                                                                    |
|  PASS  | 784: Move Operator (copy.get_data() != nullptr)                                                                                  |
|  PASS  | 787: Move Operator (copy[i] == i)                                                                                                |
|  PASS  | 787: Move Operator (copy[i] == i)                                                                                                |
|  PASS  | 787: Move Operator (copy[i] == i)                                                                                                |
|  PASS  | 787: Move Operator (copy[i] == i)                                                                                                |
|  PASS  | 787: Move Operator (copy[i] == i)                                                                                                |
|  PASS  | 794: Index Operator (vec[0] == 0)                                                                                                |
|  PASS  | 795: Index Operator (vec[1] == 1)                                                                                                |
|  PASS  | 796: Index Operator (vec[2] == 2)                                                                                                |
|  PASS  | 797: Index Operator (vec[3] == 3)                                                                                                |
|  PASS  | 798: Index Operator (vec[4] == 4)                                                                                                |
|  PASS  | 799: Index Operator (vec[5])                                                                                                     |
|  PASS  | 805: Const Index Operator (vec[0] == 0)                                                                                          |
|  PASS  | 806: Const Index Operator (vec[1] == 1)                                                                                          |
|  PASS  | 807: Const Index Operator (vec[2] == 2)                                                                                          |
|  PASS  | 808: Const Index Operator (vec[3] == 3)                                                                                          |
|  PASS  | 809: Const Index Operator (vec[4] == 4)                                                                                          |
|  PASS  | 810: Const Index Operator (vec[5])                                                                                               |
|  PASS  | 816: Get Capacity (vec.get_capacity() == 10)                                                                                     |
|  PASS  | 819: Get Capacity (vec2.get_capacity() == 0)                                                                                     |
|  PASS  | 825: Get Size (vec.get_size() == 0)                                                                                              |
|  PASS  | 828: Get Size (vec.get_size() == 5)                                                                                              |
|  PASS  | 834: Get Data (vec.get_data() != nullptr)                                                                                        |
|  PASS  | 836: Get Data (vec2.get_data() == nullptr)                                                                                       |
|  PASS  | 842: Const Get Data (vec.get_data() != nullptr)                                                                                  |
|  PASS  | 844: Const Get Data (vec2.get_data() == nullptr)                                                                                 |
|  PASS  | 851: Reserve (vec.get_capacity() == 20)                                                                                          |
|  PASS  | 853: Reserve (vec.get_capacity() == 20)                                                                                          |
|  PASS  | 860: Resize (vec.get_size() == 5)                                                                                                |
|  PASS  | 862: Resize (vec.get_size() == 10)                                                                                               |
|  PASS  | 864: Resize (vec.get_size() == 0)                                                                                                |
|  PASS  | 865: Resize (vec.get_capacity() == 10)                                                                                           |
|  PASS  | 867: Resize (vec.get_size() == 20)                                                                                               |
|  PASS  | 868: Resize (vec.get_capacity() == 20)                                                                                           |
|  PASS  | 876: Add Copy (vec.get_size() == 1)                                                                                              |
|  PASS  | 877: Add Copy (vec[0] == "5")                                                                                                    |
|  PASS  | 880: Add Copy (vec.get_size() == 2)                                                                                              |
|  PASS  | 881: Add Copy (vec[1] == "10")                                                                                                   |
|  PASS  | 889: Add Move (vec.get_size() == 1)                                                                                              |
|  PASS  | 890: Add Move (vec[0] == "5")                                                                                                    |
|  PASS  | 893: Add Move (vec.get_size() == 2)                                                                                              |
|  PASS  | 894: Add Move (vec[1] == "10")                                                                                                   |
|  PASS  | 902: Add Range (vec.get_size() == 5)                                                                                             |
|  PASS  | 903: Add Range (vec[0] == 0)                                                                                                     |
|  PASS  | 904: Add Range (vec[1] == 1)                                                                                                     |
|  PASS  | 905: Add Range (vec[2] == 2)                                                                                                     |
|  PASS  | 906: Add Range (vec[3] == 3)                                                                                                     |
|  PASS  | 907: Add Range (vec[4] == 4)                                                                                                     |
|  PASS  | 914: Insert Index Copy (vec.get_size() == 6)                                                                                     |
|  PASS  | 915: Insert Index Copy (vec[0] == 0)                                                                                             |
|  PASS  | 916: Insert Index Copy (vec[1] == 1)                                                                                             |
|  PASS  | 917: Insert Index Copy (vec[2] == 5)                                                                                             |
|  PASS  | 918: Insert Index Copy (vec[3] == 2)                                                                                             |
|  PASS  | 919: Insert Index Copy (vec[4] == 3)                                                                                             |
|  PASS  | 920: Insert Index Copy (vec[5] == 4)                                                                                             |
|  PASS  | 922: Insert Index Copy (vec.get_size() == 7)                                                                                     |
|  PASS  | 923: Insert Index Copy (vec[0] == 6)                                                                                             |
|  PASS  | 924: Insert Index Copy (vec[1] == 0)                                                                                             |
|  PASS  | 925: Insert Index Copy (vec[2] == 1)                                                                                             |
|  PASS  | 926: Insert Index Copy (vec[3] == 5)                                                                                             |
|  PASS  | 927: Insert Index Copy (vec[4] == 2)                                                                                             |
|  PASS  | 928: Insert Index Copy (vec[5] == 3)                                                                                             |
|  PASS  | 929: Insert Index Copy (vec[6] == 4)                                                                                             |
|  PASS  | 931: Insert Index Copy (vec.get_size() == 8)                                                                                     |
|  PASS  | 932: Insert Index Copy (vec[0] == 6)                                                                                             |
|  PASS  | 933: Insert Index Copy (vec[1] == 0)                                                                                             |
|  PASS  | 934: Insert Index Copy (vec[2] == 1)                                                                                             |
|  PASS  | 935: Insert Index Copy (vec[3] == 5)                                                                                             |
|  PASS  | 936: Insert Index Copy (vec[4] == 2)                                                                                             |
|  PASS  | 937: Insert Index Copy (vec[5] == 3)                                                                                             |
|  PASS  | 938: Insert Index Copy (vec[6] == 4)                                                                                             |
|  PASS  | 939: Insert Index Copy (vec[7] == 7)                                                                                             |
|  PASS  | 947: Insert Index Move (vec.get_size() == 6)                                                                                     |
|  PASS  | 948: Insert Index Move (vec[0] == "0")                                                                                           |
|  PASS  | 949: Insert Index Move (vec[1] == "1")                                                                                           |
|  PASS  | 950: Insert Index Move (vec[2] == "5")                                                                                           |
|  PASS  | 951: Insert Index Move (vec[3] == "2")                                                                                           |
|  PASS  | 952: Insert Index Move (vec[4] == "3")                                                                                           |
|  PASS  | 953: Insert Index Move (vec[5] == "4")                                                                                           |
|  PASS  | 956: Insert Index Move (vec.get_size() == 7)                                                                                     |
|  PASS  | 957: Insert Index Move (vec[0] == "6")                                                                                           |
|  PASS  | 958: Insert Index Move (vec[1] == "0")                                                                                           |
|  PASS  | 959: Insert Index Move (vec[2] == "1")                                                                                           |
|  PASS  | 960: Insert Index Move (vec[3] == "5")                                                                                           |
|  PASS  | 961: Insert Index Move (vec[4] == "2")                                                                                           |
|  PASS  | 962: Insert Index Move (vec[5] == "3")                                                                                           |
|  PASS  | 963: Insert Index Move (vec[6] == "4")                                                                                           |
|  PASS  | 966: Insert Index Move (vec.get_size() == 8)                                                                                     |
|  PASS  | 967: Insert Index Move (vec[0] == "6")                                                                                           |
|  PASS  | 968: Insert Index Move (vec[1] == "0")                                                                                           |
|  PASS  | 969: Insert Index Move (vec[2] == "1")                                                                                           |
|  PASS  | 970: Insert Index Move (vec[3] == "5")                                                                                           |
|  PASS  | 971: Insert Index Move (vec[4] == "2")                                                                                           |
|  PASS  | 972: Insert Index Move (vec[5] == "3")                                                                                           |
|  PASS  | 973: Insert Index Move (vec[6] == "4")                                                                                           |
|  PASS  | 974: Insert Index Move (vec[7] == "7")                                                                                           |
|  PASS  | 982: Insert Iterator Copy (vec.get_size() == 8)                                                                                  |
|  PASS  | 983: Insert Iterator Copy (vec[0] == 0)                                                                                          |
|  PASS  | 984: Insert Iterator Copy (vec[1] == 1)                                                                                          |
|  PASS  | 985: Insert Iterator Copy (vec[2] == 5)                                                                                          |
|  PASS  | 986: Insert Iterator Copy (vec[3] == 6)                                                                                          |
|  PASS  | 987: Insert Iterator Copy (vec[4] == 7)                                                                                          |
|  PASS  | 988: Insert Iterator Copy (vec[5] == 2)                                                                                          |
|  PASS  | 989: Insert Iterator Copy (vec[6] == 3)                                                                                          |
|  PASS  | 990: Insert Iterator Copy (vec[7] == 4)                                                                                          |
|  PASS  | 998: Insert Iterator Move (vec.get_size() == 8)                                                                                  |
|  PASS  | 999: Insert Iterator Move (vec[0] == "0")                                                                                        |
|  PASS  | 1000: Insert Iterator Move (vec[1] == "1")                                                                                       |
|  PASS  | 1001: Insert Iterator Move (vec[2] == "5")                                                                                       |
|  PASS  | 1002: Insert Iterator Move (vec[3] == "6")                                                                                       |
|  PASS  | 1003: Insert Iterator Move (vec[4] == "7")                                                                                       |
|  PASS  | 1004: Insert Iterator Move (vec[5] == "2")                                                                                       |
|  PASS  | 1005: Insert Iterator Move (vec[6] == "3")                                                                                       |
|  PASS  | 1006: Insert Iterator Move (vec[7] == "4")                                                                                       |
|  PASS  | 1014: Insert Index Range (vec.get_size() == 8)                                                                                   |
|  PASS  | 1015: Insert Index Range (vec[0] == 0)                                                                                           |
|  PASS  | 1016: Insert Index Range (vec[1] == 1)                                                                                           |
|  PASS  | 1017: Insert Index Range (vec[2] == 5)                                                                                           |
|  PASS  | 1018: Insert Index Range (vec[3] == 6)                                                                                           |
|  PASS  | 1019: Insert Index Range (vec[4] == 7)                                                                                           |
|  PASS  | 1020: Insert Index Range (vec[5] == 2)                                                                                           |
|  PASS  | 1021: Insert Index Range (vec[6] == 3)                                                                                           |
|  PASS  | 1022: Insert Index Range (vec[7] == 4)                                                                                           |
|  PASS  | 1030: Insert Iterator Range (vec.get_size() == 8)                                                                                |
|  PASS  | 1031: Insert Iterator Range (vec[0] == 0)                                                                                        |
|  PASS  | 1032: Insert Iterator Range (vec[1] == 1)                                                                                        |
|  PASS  | 1033: Insert Iterator Range (vec[2] == 5)                                                                                        |
|  PASS  | 1034: Insert Iterator Range (vec[3] == 6)                                                                                        |
|  PASS  | 1035: Insert Iterator Range (vec[4] == 7)                                                                                        |
|  PASS  | 1036: Insert Iterator Range (vec[5] == 2)                                                                                        |
|  PASS  | 1037: Insert Iterator Range (vec[6] == 3)                                                                                        |
|  PASS  | 1038: Insert Iterator Range (vec[7] == 4)                                                                                        |
|  PASS  | 1045: Remove Index (vec.get_size() == 4)                                                                                         |
|  PASS  | 1046: Remove Index (vec[0] == 0)                                                                                                 |
|  PASS  | 1047: Remove Index (vec[1] == 1)                                                                                                 |
|  PASS  | 1048: Remove Index (vec[2] == 3)                                                                                                 |
|  PASS  | 1049: Remove Index (vec[3] == 4)                                                                                                 |
|  PASS  | 1051: Remove Index (vec.get_size() == 3)                                                                                         |
|  PASS  | 1052: Remove Index (vec[0] == 1)                                                                                                 |
|  PASS  | 1053: Remove Index (vec[1] == 3)                                                                                                 |
|  PASS  | 1054: Remove Index (vec[2] == 4)                                                                                                 |
|  PASS  | 1056: Remove Index (vec.get_size() == 2)                                                                                         |
|  PASS  | 1057: Remove Index (vec[0] == 1)                                                                                                 |
|  PASS  | 1058: Remove Index (vec[1] == 3)                                                                                                 |
|  PASS  | 1060: Remove Index (vec.get_size() == 1)                                                                                         |
|  PASS  | 1061: Remove Index (vec[0] == 1)                                                                                                 |
|  PASS  | 1063: Remove Index (vec.get_size() == 0)                                                                                         |
|  PASS  | 1070: Remove Iterator (vec.get_size() == 4)                                                                                      |
|  PASS  | 1071: Remove Iterator (vec[0] == 0)                                                                                              |
|  PASS  | 1072: Remove Iterator (vec[1] == 1)                                                                                              |
|  PASS  | 1073: Remove Iterator (vec[2] == 3)                                                                                              |
|  PASS  | 1074: Remove Iterator (vec[3] == 4)                                                                                              |
|  PASS  | 1076: Remove Iterator (vec.get_size() == 3)                                                                                      |
|  PASS  | 1077: Remove Iterator (vec[0] == 1)                                                                                              |
|  PASS  | 1078: Remove Iterator (vec[1] == 3)                                                                                              |
|  PASS  | 1079: Remove Iterator (vec[2] == 4)                                                                                              |
|  PASS  | 1081: Remove Iterator (vec.get_size() == 2)                                                                                      |
|  PASS  | 1082: Remove Iterator (vec[0] == 1)                                                                                              |
|  PASS  | 1083: Remove Iterator (vec[1] == 3)                                                                                              |
|  PASS  | 1085: Remove Iterator (vec.get_size() == 1)                                                                                      |
|  PASS  | 1086: Remove Iterator (vec[0] == 1)                                                                                              |
|  PASS  | 1088: Remove Iterator (vec.get_size() == 0)                                                                                      |
|  PASS  | 1094: Remove Index Range (vec.remove(0, 0))                                                                                      |
|  PASS  | 1095: Remove Index Range (vec.remove(5, 1))                                                                                      |
|  PASS  | 1096: Remove Index Range (vec.remove(0, 6))                                                                                      |
|  PASS  | 1098: Remove Index Range (vec.get_size() == 2)                                                                                   |
|  PASS  | 1099: Remove Index Range (vec[0] == 0)                                                                                           |
|  PASS  | 1100: Remove Index Range (vec[1] == 4)                                                                                           |
|  PASS  | 1102: Remove Index Range (vec.get_size() == 1)                                                                                   |
|  PASS  | 1103: Remove Index Range (vec[0] == 4)                                                                                           |
|  PASS  | 1104: Remove Index Range (vec.get_size() == 1)                                                                                   |
|  PASS  | 1105: Remove Index Range (vec[0] == 4)                                                                                           |
|  PASS  | 1107: Remove Index Range (vec.get_size() == 0)                                                                                   |
|  PASS  | 1114: Remove Iterator Range (vec.get_size() == 2)                                                                                |
|  PASS  | 1115: Remove Iterator Range (vec[0] == 0)                                                                                        |
|  PASS  | 1116: Remove Iterator Range (vec[1] == 4)                                                                                        |
|  PASS  | 1118: Remove Iterator Range (vec.get_size() == 1)                                                                                |
|  PASS  | 1119: Remove Iterator Range (vec[0] == 4)                                                                                        |
|  PASS  | 1120: Remove Iterator Range (vec.remove(vec.begin(), vec.begin()))                                                               |
|  PASS  | 1121: Remove Iterator Range (vec.get_size() == 1)                                                                                |
|  PASS  | 1122: Remove Iterator Range (vec[0] == 4)                                                                                        |
|  PASS  | 1124: Remove Iterator Range (vec.get_size() == 0)                                                                                |
|  PASS  | 1130: Is Empty (vec.is_empty())                                                                                                  |
|  PASS  | 1132: Is Empty (!vec.is_empty())                                                                                                 |
|  PASS  | 1134: Is Empty (vec.is_empty())                                                                                                  |
|  PASS  | 1140: At (vec.at(0) == 0)                                                                                                        |
|  PASS  | 1141: At (vec.at(1) == 1)                                                                                                        |
|  PASS  | 1142: At (vec.at(2) == 2)                                                                                                        |
|  PASS  | 1143: At (vec.at(3) == 3)                                                                                                        |
|  PASS  | 1144: At (vec.at(4) == 4)                                                                                                        |
|  PASS  | 1145: At (vec.at(5))                                                                                                             |
|  PASS  | 1147: At (vec.at(0) == 5)                                                                                                        |
|  PASS  | 1153: Const At (vec.at(0) == 0)                                                                                                  |
|  PASS  | 1154: Const At (vec.at(1) == 1)                                                                                                  |
|  PASS  | 1155: Const At (vec.at(2) == 2)                                                                                                  |
|  PASS  | 1156: Const At (vec.at(3) == 3)                                                                                                  |
|  PASS  | 1157: Const At (vec.at(4) == 4)                                                                                                  |
|  PASS  | 1158: Const At (vec.at(5))                                                                                                       |
|  PASS  | 1165: Sub (sub.get_size() == 2)                                                                                                  |
|  PASS  | 1166: Sub (sub[0] == 2)                                                                                                          |
|  PASS  | 1167: Sub (sub[1] == 3)                                                                                                          |
|  PASS  | 1173: Find (vec.find(0) == vec.begin())                                                                                          |
|  PASS  | 1174: Find (vec.find(1) == vec.begin() + 1)                                                                                      |
|  PASS  | 1175: Find (vec.find(2) == vec.begin() + 2)                                                                                      |
|  PASS  | 1176: Find (vec.find(3) == vec.begin() + 3)                                                                                      |
|  PASS  | 1177: Find (vec.find(4) == vec.begin() + 4)                                                                                      |
|  PASS  | 1178: Find (vec.find(5) == vec.end())                                                                                            |
|  PASS  | 1184: Const Find (vec.find(0) == vec.begin())                                                                                    |
|  PASS  | 1185: Const Find (vec.find(1) == vec.begin() + 1)                                                                                |
|  PASS  | 1186: Const Find (vec.find(2) == vec.begin() + 2)                                                                                |
|  PASS  | 1187: Const Find (vec.find(3) == vec.begin() + 3)                                                                                |
|  PASS  | 1188: Const Find (vec.find(4) == vec.begin() + 4)                                                                                |
|  PASS  | 1189: Const Find (vec.find(5) == vec.end())                                                                                      |
|  PASS  | 1195: Contains (vec.contains(0))                                                                                                 |
|  PASS  | 1196: Contains (vec.contains(1))                                                                                                 |
|  PASS  | 1197: Contains (vec.contains(2))                                                                                                 |
|  PASS  | 1198: Contains (vec.contains(3))                                                                                                 |
|  PASS  | 1199: Contains (vec.contains(4))                                                                                                 |
|  PASS  | 1200: Contains (!vec.contains(5))                                                                                                |
|  PASS  | 1207: Clear (vec.get_size() == 0)                                                                                                |
|  PASS  | 1208: Clear (vec.get_capacity() == 5)                                                                                            |
|  PASS  | 1209: Clear (vec.get_data() != nullptr)                                                                                          |
|  PASS  | 1215: Begin (*vec.begin() == 0)                                                                                                  |
|  PASS  | 1221: Const Begin (*vec.begin() == 0)                                                                                            |
|  PASS  | 1227: End (vec.end() == vec.begin() + 5)                                                                                         |
|  PASS  | 1233: Const End (vec.end() == vec.begin() + 5)                                                                                   |
|  PASS  | 1239: Reverse Begin (*vec.rbegin() == 4)                                                                                         |
|  PASS  | 1245: Reverse End (vec.rend() == vec.rbegin() + 5)                                                                               |
|  PASS  | 1251: Const Reverse Begin (*vec.rbegin() == 4)                                                                                   |
|  PASS  | 1257: Const Reverse End (vec.rend() == vec.rbegin() + 5)                                                                         |

## File
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 14: Copy (Path::exists(TEST_PATH_2) == true)                                                                                     |
|  PASS  | 15: Copy (Path::exists(TEST_PATH) == true)                                                                                       |
|  PASS  | 17: Copy (Path::exists(TEST_PATH_2) == false)                                                                                    |
|  PASS  | 23: Move (Path::exists(TEST_PATH_2) == true)                                                                                     |
|  PASS  | 24: Move (Path::exists(TEST_PATH) == false)                                                                                      |
|  PASS  | 26: Move (Path::exists(TEST_PATH) == true)                                                                                       |
|  PASS  | 27: Move (Path::exists(TEST_PATH_2) == false)                                                                                    |
|  PASS  | 33: Create (Path::exists(TEST_PATH_2) == true)                                                                                   |
|  PASS  | 35: Create (Path::exists(TEST_PATH_2) == false)                                                                                  |
|  PASS  | 41: Destroy (Path::exists(TEST_PATH_2) == true)                                                                                  |
|  PASS  | 43: Destroy (Path::exists(TEST_PATH_2) == false)                                                                                 |

## PhysicalFile
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 16: Default Constructor (file.get_path().is_empty())                                                                             |
|  PASS  | 17: Default Constructor (file.get_flags() == File::Flags::None)                                                                  |
|  PASS  | 18: Default Constructor (file.is_open() == false)                                                                                |
|  PASS  | 24: Open Constructor (file.get_path().is_empty() == false)                                                                       |
|  PASS  | 25: Open Constructor (file.get_flags() == File::Flags::Read)                                                                     |
|  PASS  | 26: Open Constructor (file.is_open() == true)                                                                                    |
|  PASS  | 32: Get Path (file.get_path() == TEST_FILE_PATH)                                                                                 |
|  PASS  | 38: Get Flags (file.get_flags() == File::Flags::Read)                                                                            |
|  PASS  | 40: Get Flags (file2.get_flags() == File::Flags::None)                                                                           |
|  PASS  | 48: Get Size (file2.get_size() == 0)                                                                                             |
|  PASS  | 51: Get Size (file2.get_size() == TEST_TEXT_LENGTH)                                                                              |
|  PASS  | 56: Get Size (file4.get_size() == 0)                                                                                             |
|  PASS  | 63: Is Open (file.is_open() == true)                                                                                             |
|  PASS  | 65: Is Open (file.is_open() == false)                                                                                            |
|  PASS  | 67: Is Open (file2.is_open() == false)                                                                                           |
|  PASS  | 69: Is Open (file.is_open() == true)                                                                                             |
|  PASS  | 76: Open (file.get_path() == TEST_FILE_PATH)                                                                                     |
|  PASS  | 77: Open (file.get_flags() == File::Flags::Read)                                                                                 |
|  PASS  | 78: Open (file.is_open() == true)                                                                                                |
|  PASS  | 80: Open (file.get_path() == TEST_FILE_PATH)                                                                                     |
|  PASS  | 81: Open (file.get_flags() == File::Flags::Read)                                                                                 |
|  PASS  | 82: Open (file.is_open() == true)                                                                                                |
|  PASS  | 84: Open (file.is_open() == false)                                                                                               |
|  PASS  | 94: Flush (file2.get_size() == TEST_TEXT_LENGTH)                                                                                 |
|  PASS  | 102: Close (file.is_open() == false)                                                                                             |
|  PASS  | 112: Seek (file2.tell() == TEST_TEXT_LENGTH)                                                                                     |
|  PASS  | 114: Seek (file2.tell() == 0)                                                                                                    |
|  PASS  | 116: Seek (file2.tell() == 0)                                                                                                    |
|  PASS  | 118: Seek (file2.tell() == TEST_TEXT_LENGTH)                                                                                     |
|  PASS  | 129: Seek Read (file2.tell_read() == TEST_TEXT_LENGTH)                                                                           |
|  PASS  | 131: Seek Read (file2.tell_read() == 0)                                                                                          |
|  PASS  | 133: Seek Read (file2.tell_read() == 0)                                                                                          |
|  PASS  | 135: Seek Read (file2.tell_read() == TEST_TEXT_LENGTH)                                                                           |
|  PASS  | 147: Seek Write (file2.tell_write() == TEST_TEXT_LENGTH)                                                                         |
|  PASS  | 149: Seek Write (file2.tell_write() == 0)                                                                                        |
|  PASS  | 151: Seek Write (file2.tell_write() == 0)                                                                                        |
|  PASS  | 153: Seek Write (file2.tell_write() == TEST_TEXT_LENGTH)                                                                         |
|  PASS  | 163: End Of File (file2.end_of_file() == false)                                                                                  |
|  PASS  | 166: End Of File (file2.end_of_file() == true)                                                                                   |
|  PASS  | 176: Tell (file2.tell() == 0)                                                                                                    |
|  PASS  | 178: Tell (file2.tell() == TEST_TEXT_SIZE)                                                                                       |
|  PASS  | 180: Tell (file2.tell() == 0)                                                                                                    |
|  PASS  | 182: Tell (file2.tell() == 0)                                                                                                    |
|  PASS  | 184: Tell (file2.tell() == TEST_TEXT_SIZE)                                                                                       |
|  PASS  | 194: Tell Read (file2.tell_read() == 0)                                                                                          |
|  PASS  | 196: Tell Read (file2.tell_read() == TEST_TEXT_SIZE)                                                                             |
|  PASS  | 198: Tell Read (file2.tell_read() == 0)                                                                                          |
|  PASS  | 200: Tell Read (file2.tell_read() == 0)                                                                                          |
|  PASS  | 202: Tell Read (file2.tell_read() == TEST_TEXT_SIZE)                                                                             |
|  PASS  | 213: Tell Write (file2.tell_write() == TEST_TEXT_SIZE)                                                                           |
|  PASS  | 215: Tell Write (file2.tell_write() == TEST_TEXT_SIZE)                                                                           |
|  PASS  | 217: Tell Write (file2.tell_write() == 0)                                                                                        |
|  PASS  | 219: Tell Write (file2.tell_write() == 0)                                                                                        |
|  PASS  | 221: Tell Write (file2.tell_write() == TEST_TEXT_SIZE)                                                                           |
|  PASS  | 231: Peek (file2.peek() == 'H')                                                                                                  |
|  PASS  | 233: Peek (file2.peek() == '\0')                                                                                                 |
|  PASS  | 248: Read Char (file2.read() == text[i])                                                                                         |
|  PASS  | 248: Read Char (file2.read() == text[i])                                                                                         |
|  PASS  | 248: Read Char (file2.read() == text[i])                                                                                         |
|  PASS  | 248: Read Char (file2.read() == text[i])                                                                                         |
|  PASS  | 248: Read Char (file2.read() == text[i])                                                                                         |
|  PASS  | 248: Read Char (file2.read() == text[i])                                                                                         |
|  PASS  | 248: Read Char (file2.read() == text[i])                                                                                         |
|  PASS  | 248: Read Char (file2.read() == text[i])                                                                                         |
|  PASS  | 248: Read Char (file2.read() == text[i])                                                                                         |
|  PASS  | 248: Read Char (file2.read() == text[i])                                                                                         |
|  PASS  | 248: Read Char (file2.read() == text[i])                                                                                         |
|  PASS  | 248: Read Char (file2.read() == text[i])                                                                                         |
|  PASS  | 248: Read Char (file2.read() == text[i])                                                                                         |
|  PASS  | 266: Read Buffer (buffer[i] == text[i])                                                                                          |
|  PASS  | 266: Read Buffer (buffer[i] == text[i])                                                                                          |
|  PASS  | 266: Read Buffer (buffer[i] == text[i])                                                                                          |
|  PASS  | 266: Read Buffer (buffer[i] == text[i])                                                                                          |
|  PASS  | 266: Read Buffer (buffer[i] == text[i])                                                                                          |
|  PASS  | 266: Read Buffer (buffer[i] == text[i])                                                                                          |
|  PASS  | 266: Read Buffer (buffer[i] == text[i])                                                                                          |
|  PASS  | 266: Read Buffer (buffer[i] == text[i])                                                                                          |
|  PASS  | 266: Read Buffer (buffer[i] == text[i])                                                                                          |
|  PASS  | 266: Read Buffer (buffer[i] == text[i])                                                                                          |
|  PASS  | 266: Read Buffer (buffer[i] == text[i])                                                                                          |
|  PASS  | 266: Read Buffer (buffer[i] == text[i])                                                                                          |
|  PASS  | 266: Read Buffer (buffer[i] == text[i])                                                                                          |
|  PASS  | 278: Read Line (file2.read_line(line) == true)                                                                                   |
|  PASS  | 279: Read Line (line == TEST_TEXT)                                                                                               |
|  PASS  | 284: Read Line (file4.read_line(line) == false)                                                                                  |
|  PASS  | 297: Write (strcmp(buffer, TEST_TEXT) == 0)                                                                                      |

## VirtualFile
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 26: Default Constructor (file.get_path().is_empty())                                                                             |
|  PASS  | 27: Default Constructor (file.get_flags() == File::Flags::None)                                                                  |
|  PASS  | 28: Default Constructor (file.is_open() == false)                                                                                |
|  PASS  | 34: Open Constructor (file.get_path().is_empty() == false)                                                                       |
|  PASS  | 35: Open Constructor (file.get_flags() == File::Flags::Read)                                                                     |
|  PASS  | 36: Open Constructor (file.is_open() == true)                                                                                    |
|  PASS  | 37: Open Constructor (file.get_virtual_offset() == 0)                                                                            |
|  PASS  | 38: Open Constructor (file.get_virtual_size() == TEST_TEXT_1_LENGTH)                                                             |
|  PASS  | 40: Open Constructor (file.get_path().is_empty() == false)                                                                       |
|  PASS  | 41: Open Constructor (file.get_flags() == File::Flags::Read)                                                                     |
|  PASS  | 42: Open Constructor (file.is_open() == true)                                                                                    |
|  PASS  | 43: Open Constructor (file.get_virtual_offset() == TEST_TEXT_1_LENGTH)                                                           |
|  PASS  | 44: Open Constructor (file.get_virtual_size() == TEST_TEXT_2_LENGTH)                                                             |
|  PASS  | 50: Get Path (file.get_path() == TEST_FILE_PATH)                                                                                 |
|  PASS  | 56: Get Flags (file.get_flags() == File::Flags::Read)                                                                            |
|  PASS  | 62: Get Size (file.get_size() == TEST_TEXT_1_LENGTH)                                                                             |
|  PASS  | 64: Get Size (file.get_size() == TEST_TEXT_2_LENGTH)                                                                             |
|  PASS  | 70: Get Virtual Offset (file.get_virtual_offset() == 0)                                                                          |
|  PASS  | 72: Get Virtual Offset (file.get_virtual_offset() == TEST_TEXT_1_LENGTH)                                                         |
|  PASS  | 78: Get Virtual Size (file.get_virtual_size() == TEST_TEXT_1_LENGTH)                                                             |
|  PASS  | 80: Get Virtual Size (file.get_virtual_size() == TEST_TEXT_2_LENGTH)                                                             |
|  PASS  | 86: Is Open (file.is_open() == true)                                                                                             |
|  PASS  | 88: Is Open (file.is_open() == false)                                                                                            |
|  PASS  | 94: Open (file.open(TEST_FILE_PATH, File::Flags::Read, 0, TEST_TEXT_1_LENGTH))                                                   |
|  PASS  | 95: Open (file.get_path() == TEST_FILE_PATH)                                                                                     |
|  PASS  | 96: Open (file.get_flags() == File::Flags::Read)                                                                                 |
|  PASS  | 97: Open (file.is_open() == true)                                                                                                |
|  PASS  | 98: Open (file.get_virtual_offset() == 0)                                                                                        |
|  PASS  | 99: Open (file.get_virtual_size() == TEST_TEXT_1_LENGTH)                                                                         |
|  PASS  | 100: Open (file.open(TEST_FILE_PATH, File::Flags::ReadWrite, TEST_TEXT_1_LENGTH, TEST_TEXT_2_LENGTH))                            |
|  PASS  | 101: Open (file.get_path() == TEST_FILE_PATH)                                                                                    |
|  PASS  | 102: Open (file.get_flags() == File::Flags::ReadWrite)                                                                           |
|  PASS  | 103: Open (file.is_open() == true)                                                                                               |
|  PASS  | 104: Open (file.get_virtual_offset() == TEST_TEXT_1_LENGTH)                                                                      |
|  PASS  | 105: Open (file.get_virtual_size() == TEST_TEXT_2_LENGTH)                                                                        |
|  PASS  | 107: Open (file.open(TEST_FILE_PATH, File::Flags::Write | File::Flags::Truncate, 0, TEST_TEXT_1_LENGTH))                         |
|  PASS  | 108: Open (file.open(TEST_FILE_PATH, File::Flags::Append, 0, TEST_TEXT_1_LENGTH))                                                |
|  PASS  | 109: Open (file.open(TEST_FILE_PATH, File::Flags::Write, 0, TEST_TEXT_1_LENGTH))                                                 |
|  PASS  | 122: Flush (read == test)                                                                                                        |
|  PASS  | 134: Close (file.is_open() == false)                                                                                             |
|  PASS  | 141: Seek (file.tell() == 0)                                                                                                     |
|  PASS  | 143: Seek (file.tell() == 1)                                                                                                     |
|  PASS  | 145: Seek (file.tell() == TEST_TEXT_1_LENGTH)                                                                                    |
|  PASS  | 147: Seek (file.tell() == TEST_TEXT_1_LENGTH - 1)                                                                                |
|  PASS  | 154: Seek Read (file.tell_read() == 0)                                                                                           |
|  PASS  | 156: Seek Read (file.tell_read() == 1)                                                                                           |
|  PASS  | 158: Seek Read (file.tell_read() == TEST_TEXT_1_LENGTH)                                                                          |
|  PASS  | 160: Seek Read (file.tell_read() == TEST_TEXT_1_LENGTH - 1)                                                                      |
|  PASS  | 167: Seek Write (file.tell_write() == 0)                                                                                         |
|  PASS  | 169: Seek Write (file.tell_write() == 1)                                                                                         |
|  PASS  | 171: Seek Write (file.tell_write() == TEST_TEXT_1_LENGTH)                                                                        |
|  PASS  | 173: Seek Write (file.tell_write() == TEST_TEXT_1_LENGTH - 1)                                                                    |
|  PASS  | 181: End Of File (file.end_of_file() == false)                                                                                   |
|  PASS  | 184: End Of File (file.end_of_file() == true)                                                                                    |
|  PASS  | 190: Tell (file.tell() == 0)                                                                                                     |
|  PASS  | 192: Tell (file.tell() == 1)                                                                                                     |
|  PASS  | 194: Tell (file.tell() == TEST_TEXT_1_LENGTH)                                                                                    |
|  PASS  | 196: Tell (file.tell() == TEST_TEXT_1_LENGTH - 1)                                                                                |
|  PASS  | 202: Tell Read (file.tell_read() == 0)                                                                                           |
|  PASS  | 204: Tell Read (file.tell_read() == 1)                                                                                           |
|  PASS  | 206: Tell Read (file.tell_read() == TEST_TEXT_1_LENGTH)                                                                          |
|  PASS  | 208: Tell Read (file.tell_read() == TEST_TEXT_1_LENGTH - 1)                                                                      |
|  PASS  | 214: Tell Write (file.tell_write() == 0)                                                                                         |
|  PASS  | 216: Tell Write (file.tell_write() == 1)                                                                                         |
|  PASS  | 218: Tell Write (file.tell_write() == TEST_TEXT_1_LENGTH)                                                                        |
|  PASS  | 220: Tell Write (file.tell_write() == TEST_TEXT_1_LENGTH - 1)                                                                    |
|  PASS  | 228: Peek (file.peek() == TEST_TEXT[0])                                                                                          |
|  PASS  | 230: Peek (file.peek() == TEST_TEXT[1])                                                                                          |
|  PASS  | 232: Peek (file.peek() == '\0')                                                                                                  |
|  PASS  | 234: Peek (file.peek() == TEST_TEXT[TEST_TEXT_1_LENGTH - 1])                                                                     |
|  PASS  | 240: Read (file.read() == TEST_TEXT[0])                                                                                          |
|  PASS  | 241: Read (file.read() == TEST_TEXT[1])                                                                                          |
|  PASS  | 243: Read (file.read() == TEST_TEXT[TEST_TEXT_1_LENGTH - 1])                                                                     |
|  PASS  | 244: Read (file.read() == '\0')                                                                                                  |
|  PASS  | 252: Read Buffer (memcmp(buffer, TEST_TEXT_1, TEST_TEXT_1_SIZE) == 0)                                                            |
|  PASS  | 260: Read Line (line == TEST_TEXT_1)                                                                                             |
|  PASS  | 271: Write (memcmp(buffer, TEST_TEXT_1, TEST_TEXT_1_SIZE) == 0)                                                                  |

## MemoryManager
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 27: Constructor (manager.get_dynamic_size() == 0)                                                                                |
|  PASS  | 28: Constructor (manager.get_static_size() == 0)                                                                                 |
|  PASS  | 38: Move Constructor (manager.get_dynamic_size() == 0)                                                                           |
|  PASS  | 39: Move Constructor (manager.get_static_size() == 0)                                                                            |
|  PASS  | 40: Move Constructor (copy.get_dynamic_size() == 24)                                                                             |
|  PASS  | 41: Move Constructor (copy.get_static_size() == 48)                                                                              |
|  PASS  | 42: Move Constructor (copy.deallocate(def, 24, Allocator::Default))                                                              |
|  PASS  | 52: Move Operator (manager.get_dynamic_size() == 0)                                                                              |
|  PASS  | 53: Move Operator (manager.get_static_size() == 0)                                                                               |
|  PASS  | 54: Move Operator (copy.get_dynamic_size() == 24)                                                                                |
|  PASS  | 55: Move Operator (copy.get_static_size() == 48)                                                                                 |
|  PASS  | 56: Move Operator (copy.deallocate(def, 24, Allocator::Default))                                                                 |
|  PASS  | 62: Get Size (manager.get_size() == 0)                                                                                           |
|  PASS  | 64: Get Size (manager.get_size() == 24)                                                                                          |
|  PASS  | 66: Get Size (manager.get_size() == 48)                                                                                          |
|  PASS  | 68: Get Size (manager.get_size() == 72)                                                                                          |
|  PASS  | 70: Get Size (manager.get_size() == 48)                                                                                          |
|  PASS  | 72: Get Size (manager.get_size() == 24)                                                                                          |
|  PASS  | 74: Get Size (manager.get_size() == 0)                                                                                           |
|  PASS  | 80: Get Static Size (manager.get_static_size() == 0)                                                                             |
|  PASS  | 82: Get Static Size (manager.get_static_size() == 24)                                                                            |
|  PASS  | 84: Get Static Size (manager.get_static_size() == 48)                                                                            |
|  PASS  | 86: Get Static Size (manager.get_static_size() == 48)                                                                            |
|  PASS  | 88: Get Static Size (manager.get_static_size() == 48)                                                                            |
|  PASS  | 90: Get Static Size (manager.get_static_size() == 24)                                                                            |
|  PASS  | 92: Get Static Size (manager.get_static_size() == 0)                                                                             |
|  PASS  | 98: Get Dynamic Size (manager.get_dynamic_size() == 0)                                                                           |
|  PASS  | 100: Get Dynamic Size (manager.get_dynamic_size() == 0)                                                                          |
|  PASS  | 102: Get Dynamic Size (manager.get_dynamic_size() == 0)                                                                          |
|  PASS  | 104: Get Dynamic Size (manager.get_dynamic_size() == 24)                                                                         |
|  PASS  | 106: Get Dynamic Size (manager.get_dynamic_size() == 0)                                                                          |
|  PASS  | 108: Get Dynamic Size (manager.get_dynamic_size() == 0)                                                                          |
|  PASS  | 110: Get Dynamic Size (manager.get_dynamic_size() == 0)                                                                          |
|  PASS  | 119: Update (manager.allocate(1024, Allocator::Temporary))                                                                       |
|  PASS  | 120: Update (manager.allocate(1024, Allocator::Temporary))                                                                       |
|  PASS  | 122: Update (manager.allocate(1024, Allocator::Task))                                                                            |
|  PASS  | 123: Update (manager.allocate(1024, Allocator::Task))                                                                            |
|  PASS  | 119: Update (manager.allocate(1024, Allocator::Temporary))                                                                       |
|  PASS  | 120: Update (manager.allocate(1024, Allocator::Temporary))                                                                       |
|  PASS  | 122: Update (manager.allocate(1024, Allocator::Task))                                                                            |
|  PASS  | 123: Update (manager.allocate(1024, Allocator::Task))                                                                            |
|  PASS  | 119: Update (manager.allocate(1024, Allocator::Temporary))                                                                       |
|  PASS  | 120: Update (manager.allocate(1024, Allocator::Temporary))                                                                       |
|  PASS  | 122: Update (manager.allocate(1024, Allocator::Task))                                                                            |
|  PASS  | 123: Update (manager.allocate(1024, Allocator::Task))                                                                            |
|  PASS  | 119: Update (manager.allocate(1024, Allocator::Temporary))                                                                       |
|  PASS  | 120: Update (manager.allocate(1024, Allocator::Temporary))                                                                       |
|  PASS  | 122: Update (manager.allocate(1024, Allocator::Task))                                                                            |
|  PASS  | 123: Update (manager.allocate(1024, Allocator::Task))                                                                            |
|  PASS  | 119: Update (manager.allocate(1024, Allocator::Temporary))                                                                       |
|  PASS  | 120: Update (manager.allocate(1024, Allocator::Temporary))                                                                       |
|  PASS  | 122: Update (manager.allocate(1024, Allocator::Task))                                                                            |
|  PASS  | 123: Update (manager.allocate(1024, Allocator::Task))                                                                            |
|  PASS  | 137: Allocate (manager.allocate(0, Allocator::Temporary))                                                                        |
|  PASS  | 138: Allocate (manager.allocate(0, Allocator::Task))                                                                             |
|  PASS  | 139: Allocate (manager.allocate(0, Allocator::Persistent))                                                                       |
|  PASS  | 140: Allocate (manager.allocate(0, Allocator::Default))                                                                          |
|  PASS  | 142: Allocate (manager.allocate(2048, Allocator::Temporary))                                                                     |
|  PASS  | 143: Allocate (manager.allocate(2048, Allocator::Task))                                                                          |
|  PASS  | 144: Allocate (manager.allocate(2048, Allocator::Persistent))                                                                    |
|  PASS  | 145: Allocate (def = manager.allocate(2048, Allocator::Default))                                                                 |
|  PASS  | 149: Allocate (temporary != nullptr)                                                                                             |
|  PASS  | 152: Allocate (task != nullptr)                                                                                                  |
|  PASS  | 155: Allocate (persistent != nullptr)                                                                                            |
|  PASS  | 158: Allocate (def != nullptr)                                                                                                   |
|  PASS  | 165: Deallocate (manager.deallocate(nullptr, 24, Allocator::Temporary))                                                          |
|  PASS  | 166: Deallocate (manager.deallocate(nullptr, 24, Allocator::Task))                                                               |
|  PASS  | 167: Deallocate (manager.deallocate(nullptr, 24, Allocator::Persistent))                                                         |
|  PASS  | 168: Deallocate (manager.deallocate(nullptr, 24, Allocator::Default))                                                            |
|  PASS  | 171: Deallocate (manager.deallocate(nullptr, 24, Allocator::Temporary))                                                          |
|  PASS  | 172: Deallocate (manager.deallocate(temporary, 0, Allocator::Temporary))                                                         |
|  PASS  | 173: Deallocate (manager.deallocate(temporary, 24, Allocator::Temporary))                                                        |
|  PASS  | 177: Deallocate (manager.deallocate(temporary, 24, Allocator::Temporary))                                                        |
|  PASS  | 180: Deallocate (manager.deallocate(nullptr, 24, Allocator::Task))                                                               |
|  PASS  | 181: Deallocate (manager.deallocate(task, 0, Allocator::Task))                                                                   |
|  PASS  | 182: Deallocate (manager.deallocate(task, 24, Allocator::Default))                                                               |
|  PASS  | 183: Deallocate (manager.deallocate(task, 24, Allocator::Task))                                                                  |
|  PASS  | 186: Deallocate (manager.deallocate(nullptr, 24, Allocator::Persistent))                                                         |
|  PASS  | 187: Deallocate (manager.deallocate(persistent, 0, Allocator::Persistent))                                                       |
|  PASS  | 188: Deallocate (manager.deallocate(persistent, 24, Allocator::Default))                                                         |
|  PASS  | 189: Deallocate (manager.deallocate(persistent, 24, Allocator::Persistent))                                                      |
|  PASS  | 192: Deallocate (manager.deallocate(nullptr, 24, Allocator::Default))                                                            |
|  PASS  | 193: Deallocate (manager.deallocate(def, 0, Allocator::Default))                                                                 |
|  PASS  | 194: Deallocate (manager.deallocate(def, 24, Allocator::Temporary))                                                              |
|  PASS  | 195: Deallocate (manager.deallocate(def, 24, Allocator::Default))                                                                |
|  PASS  | 197: Deallocate (manager.get_static_size() == 0)                                                                                 |
|  PASS  | 198: Deallocate (manager.get_dynamic_size() == 0)                                                                                |

## MemoryPool
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 16: Constructor (MemoryPool({ 0, 10 }))                                                                                          |
|  PASS  | 17: Constructor (MemoryPool({ 1024, 0 }))                                                                                        |
|  PASS  | 19: Constructor (pool.get_block_size() == 1024)                                                                                  |
|  PASS  | 20: Constructor (pool.get_capacity() == 10)                                                                                      |
|  PASS  | 21: Constructor (pool.get_count() == 0)                                                                                          |
|  PASS  | 29: Move Constructor (pool.get_block_size() == 0)                                                                                |
|  PASS  | 30: Move Constructor (pool.get_capacity() == 0)                                                                                  |
|  PASS  | 31: Move Constructor (pool.get_count() == 0)                                                                                     |
|  PASS  | 32: Move Constructor (copy.get_block_size() == 1024)                                                                             |
|  PASS  | 33: Move Constructor (copy.get_capacity() == 10)                                                                                 |
|  PASS  | 34: Move Constructor (copy.get_count() == 1)                                                                                     |
|  PASS  | 42: Move Operator (pool.get_block_size() == 0)                                                                                   |
|  PASS  | 43: Move Operator (pool.get_capacity() == 0)                                                                                     |
|  PASS  | 44: Move Operator (pool.get_count() == 0)                                                                                        |
|  PASS  | 45: Move Operator (copy.get_block_size() == 1024)                                                                                |
|  PASS  | 46: Move Operator (copy.get_capacity() == 10)                                                                                    |
|  PASS  | 47: Move Operator (copy.get_count() == 1)                                                                                        |
|  PASS  | 53: Get Block Size (pool.get_block_size() == 1024)                                                                               |
|  PASS  | 59: Get Capacity (pool.get_capacity() == 10)                                                                                     |
|  PASS  | 65: Get Count (pool.get_count() == 0)                                                                                            |
|  PASS  | 67: Get Count (pool.get_count() == 1)                                                                                            |
|  PASS  | 73: Get Data (pool.get_data() != nullptr)                                                                                        |
|  PASS  | 75: Get Data (ptr == pool.get_data())                                                                                            |
|  PASS  | 81: Is Full (!pool.is_full())                                                                                                    |
|  PASS  | 83: Is Full (pool.is_full())                                                                                                     |
|  PASS  | 90: Allocate (ptr != nullptr)                                                                                                    |
|  PASS  | 91: Allocate (pool.get_count() == 1)                                                                                             |
|  PASS  | 93: Allocate (ptr != nullptr)                                                                                                    |
|  PASS  | 94: Allocate (pool.get_count() == 2)                                                                                             |
|  PASS  | 102: Deallocate (pool.get_count() == 0)                                                                                          |
|  PASS  | 110: Clear (pool.get_count() == 0)                                                                                               |

## MemoryStack
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 15: Constructor (MemoryStack({ 0 }))                                                                                             |
|  PASS  | 17: Constructor (stack.get_capacity() == 1024)                                                                                   |
|  PASS  | 18: Constructor (stack.get_size() == 0)                                                                                          |
|  PASS  | 26: Move Constructor (stack.get_capacity() == 0)                                                                                 |
|  PASS  | 27: Move Constructor (stack.get_size() == 0)                                                                                     |
|  PASS  | 28: Move Constructor (copy.get_capacity() == 1024)                                                                               |
|  PASS  | 29: Move Constructor (copy.get_size() == 512)                                                                                    |
|  PASS  | 37: Move Operator (stack.get_capacity() == 0)                                                                                    |
|  PASS  | 38: Move Operator (stack.get_size() == 0)                                                                                        |
|  PASS  | 39: Move Operator (copy.get_capacity() == 1024)                                                                                  |
|  PASS  | 40: Move Operator (copy.get_size() == 512)                                                                                       |
|  PASS  | 46: Get Capacity (stack.get_capacity() == 1024)                                                                                  |
|  PASS  | 52: Get Size (stack.get_size() == 0)                                                                                             |
|  PASS  | 54: Get Size (stack.get_size() == 512)                                                                                           |
|  PASS  | 56: Get Size (stack.get_size() == 1024)                                                                                          |
|  PASS  | 62: Get Data (stack.get_data() != nullptr)                                                                                       |
|  PASS  | 64: Get Data (ptr == stack.get_data())                                                                                           |
|  PASS  | 71: Allocate (stack.allocate(0))                                                                                                 |
|  PASS  | 72: Allocate (ptr != nullptr)                                                                                                    |
|  PASS  | 73: Allocate (stack.get_size() == 512)                                                                                           |
|  PASS  | 75: Allocate (ptr != nullptr)                                                                                                    |
|  PASS  | 76: Allocate (stack.get_size() == 1024)                                                                                          |
|  PASS  | 77: Allocate (stack.allocate(1))                                                                                                 |
|  PASS  | 83: Deallocate (stack.deallocate(0))                                                                                             |
|  PASS  | 84: Deallocate (stack.deallocate(512))                                                                                           |
|  PASS  | 87: Deallocate (stack.get_size() == 0)                                                                                           |
|  PASS  | 95: Clear (stack.get_size() == 0)                                                                                                |

## Wrap
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 15: Default Constructor (String(wrap.get_base_path()) == "")                                                                     |
|  PASS  | 16: Default Constructor (wrap.get_content_version() == 0)                                                                        |
|  PASS  | 17: Default Constructor (wrap.get_entry_count() == 0)                                                                            |
|  PASS  | 18: Default Constructor (String(wrap.get_name()) == "")                                                                          |
|  PASS  | 19: Default Constructor (wrap.get_path().get_string() == "")                                                                     |
|  PASS  | 20: Default Constructor (wrap.get_size() == 0)                                                                                   |
|  PASS  | 21: Default Constructor (wrap.get_type() == Wrap::Type::None)                                                                    |
|  PASS  | 22: Default Constructor (wrap.get_wrap_version() == 0)                                                                           |
|  PASS  | 28: Path Constructor (String(wrap.get_base_path()) != "")                                                                        |
|  PASS  | 29: Path Constructor (wrap.get_content_version() >= 0)                                                                           |
|  PASS  | 30: Path Constructor (wrap.get_entry_count() != 0)                                                                               |
|  PASS  | 31: Path Constructor (String(wrap.get_name()) != "")                                                                             |
|  PASS  | 32: Path Constructor (wrap.get_path() == Path(TEST_PATH).get_absolute())                                                         |
|  PASS  | 33: Path Constructor (wrap.get_size() != 0)                                                                                      |
|  PASS  | 34: Path Constructor (wrap.get_type() != Wrap::Type::None)                                                                       |
|  PASS  | 40: New Constructor (String(wrap.get_base_path()) == "")                                                                         |
|  PASS  | 41: New Constructor (wrap.get_content_version() == 0)                                                                            |
|  PASS  | 42: New Constructor (wrap.get_entry_count() == 0)                                                                                |
|  PASS  | 43: New Constructor (String(wrap.get_name()) == "Test")                                                                          |
|  PASS  | 44: New Constructor (wrap.get_path() == Path(TEST_NEW_PATH).get_absolute())                                                      |
|  PASS  | 45: New Constructor (wrap.get_size() != 0)                                                                                       |
|  PASS  | 46: New Constructor (wrap.get_type() == Wrap::Type::File)                                                                        |
|  PASS  | 51: New Constructor (String(wrap2.get_base_path()) == "Test/Path")                                                               |
|  PASS  | 52: New Constructor (wrap2.get_content_version() == 34)                                                                          |
|  PASS  | 53: New Constructor (wrap2.get_entry_count() == 0)                                                                               |
|  PASS  | 54: New Constructor (String(wrap2.get_name()) == "Test Again")                                                                   |
|  PASS  | 55: New Constructor (wrap2.get_path() == Path(TEST_NEW_PATH).get_absolute())                                                     |
|  PASS  | 56: New Constructor (wrap2.get_size() != 0)                                                                                      |
|  PASS  | 57: New Constructor (wrap2.get_type() == Wrap::Type::File)                                                                       |
|  PASS  | 65: Get/Set Base Path (String(wrap.get_base_path()) == "")                                                                       |
|  PASS  | 68: Get/Set Base Path (String(wrap.get_base_path()) == "Test/Path")                                                              |
|  PASS  | 76: Get Path (wrap.get_path() == Path(TEST_NEW_PATH).get_absolute())                                                             |
|  PASS  | 83: Get/Set Name (String(wrap.get_name()) == "Test")                                                                             |
|  PASS  | 85: Get/Set Name (String(wrap.get_name()) == "Test Again")                                                                       |
|  PASS  | 92: Get Wrap Version (wrap.get_wrap_version() == WRAP_VERSION)                                                                   |
|  PASS  | 99: Get Content Version (wrap.get_content_version() == 0)                                                                        |
|  PASS  | 106: Get/Set Type (wrap.get_type() == Wrap::Type::File)                                                                          |
|  PASS  | 108: Get/Set Type (wrap.get_type() == Wrap::Type::None)                                                                          |
|  PASS  | 115: Get Size (wrap.get_size() != 0)                                                                                             |
|  PASS  | 122: Get Entry Count (wrap.get_entry_count() == 0)                                                                               |
|  PASS  | 125: Get Entry Count (wrap2.get_entry_count() == 23)                                                                             |
|  PASS  | 133: Load (String(wrap.get_base_path()) != "")                                                                                   |
|  PASS  | 134: Load (wrap.get_content_version() >= 0)                                                                                      |
|  PASS  | 135: Load (wrap.get_entry_count() != 0)                                                                                          |
|  PASS  | 136: Load (String(wrap.get_name()) != "")                                                                                        |
|  PASS  | 137: Load (wrap.get_path() == Path(TEST_PATH).get_absolute())                                                                    |
|  PASS  | 138: Load (wrap.get_size() != 0)                                                                                                 |
|  PASS  | 139: Load (wrap.get_type() != Wrap::Type::None)                                                                                  |
|  PASS  | 146: Emplace (wrap.get_entry_count() == 1)                                                                                       |
|  PASS  | 147: Emplace (wrap.get_size() != 0)                                                                                              |
|  PASS  | 158: Emplace (text.contains("Lorem ipsum"))                                                                                      |
|  PASS  | 161: Emplace (wrap.emplace(TEST_TEXT_PATH, "Text.txt", CompressionLevel::None))                                                  |
|  PASS  | 170: Contains (wrap.contains("Text.txt"))                                                                                        |
|  PASS  | 171: Contains (wrap.contains("Text2.txt") == false)                                                                              |
|  PASS  | 176: Contains (wrap2.contains("Base/Path/Text.txt"))                                                                             |
|  PASS  | 185: Open (wrap.open("Text.txt", file))                                                                                          |
|  PASS  | 194: Open (text.contains("Lorem ipsum"))                                                                                         |
|  PASS  | 206: Read (text.contains("Lorem ipsum"))                                                                                         |
|  PASS  | 214: Get Entry Index (Path(wrap.get_entry(0).path) == "Text.txt")                                                                |
|  PASS  | 222: Get Entry Path (Path(wrap.get_entry("Text.txt").path) == "Text.txt")                                                        |
|  PASS  | 230: Load Or Create (Path(wrap.get_base_path()) == "Test/Path")                                                                  |
|  PASS  | 231: Load Or Create (wrap.get_content_version() == 34)                                                                           |
|  PASS  | 232: Load Or Create (wrap.get_entry_count() == 1)                                                                                |
|  PASS  | 233: Load Or Create (String(wrap.get_name()) == "Test")                                                                          |
|  PASS  | 234: Load Or Create (wrap.get_path() == Path(TEST_NEW_PATH).get_absolute())                                                      |
|  PASS  | 235: Load Or Create (wrap.get_size() != 0)                                                                                       |
|  PASS  | 236: Load Or Create (wrap.get_type() == Wrap::Type::File)                                                                        |
|  PASS  | 240: Load Or Create (Path(wrap2.get_base_path()) == "Test/Path")                                                                 |
|  PASS  | 241: Load Or Create (wrap2.get_content_version() == 34)                                                                          |
|  PASS  | 242: Load Or Create (wrap2.get_entry_count() == 1)                                                                               |
|  PASS  | 243: Load Or Create (String(wrap2.get_name()) == "Test")                                                                         |
|  PASS  | 244: Load Or Create (wrap2.get_path() == Path(TEST_NEW_PATH).get_absolute())                                                     |
|  PASS  | 245: Load Or Create (wrap2.get_size() != 0)                                                                                      |
|  PASS  | 246: Load Or Create (wrap2.get_type() == Wrap::Type::File)                                                                       |

## Wrapper
| Result | Message                                                                                                                          |
| ------ | -------------------------------------------------------------------------------------------------------------------------------- |
|  PASS  | 19: Default Constructor (wrapper.get_wrap_count() == 0)                                                                          |
|  PASS  | 25: Get Wrap Count (wrapper.get_wrap_count() == 0)                                                                               |
|  PASS  | 27: Get Wrap Count (wrapper.get_wrap_count() == 1)                                                                               |
|  PASS  | 35: Add Wrap (wrapper.get_wrap_count() == 1)                                                                                     |
|  PASS  | 42: Add Path (wrapper.get_wrap_count() == 1)                                                                                     |
|  PASS  | 49: Get Wrap (wrapper.get_wrap(0).get_path() == Path(TEST_PATH).get_absolute())                                                  |
|  PASS  | 57: Const Get Wrap (wrapper2.get_wrap(0).get_path() == Path(TEST_PATH).get_absolute())                                           |
|  PASS  | 64: Find By Path (wrapper.find_by_path(TEST_ASSET_PATH) != nullptr)                                                              |
|  PASS  | 65: Find By Path (wrapper.find_by_path(TEST_ASSET_PATH_2) != nullptr)                                                            |
|  PASS  | 66: Find By Path (wrapper.find_by_path("Not Here") == nullptr)                                                                   |
|  PASS  | 74: Const Find By Path (wrapper2.find_by_path(TEST_ASSET_PATH) != nullptr)                                                       |
|  PASS  | 75: Const Find By Path (wrapper2.find_by_path(TEST_ASSET_PATH_2) != nullptr)                                                     |
|  PASS  | 76: Const Find By Path (wrapper2.find_by_path("Not Here") == nullptr)                                                            |
|  PASS  | 83: Find By Name (wrapper.find_by_name(TEST_NAME) != nullptr)                                                                    |
|  PASS  | 84: Find By Name (wrapper.find_by_name("Not Here") == nullptr)                                                                   |
|  PASS  | 92: Const Find By Name (wrapper2.find_by_name(TEST_NAME) != nullptr)                                                             |
|  PASS  | 93: Const Find By Name (wrapper2.find_by_name("Not Here") == nullptr)                                                            |
|  PASS  | 100: Contains (wrapper.contains(TEST_ASSET_PATH))                                                                                |
|  PASS  | 101: Contains (wrapper.contains(TEST_ASSET_PATH_2))                                                                              |
|  PASS  | 102: Contains (!wrapper.contains("Not Here"))                                                                                    |
|  PASS  | 110: Open (wrapper.open(TEST_ASSET_PATH, file))                                                                                  |
|  PASS  | 119: Read (data.get_size() != 0)                                                                                                 |
|  PASS  | 122: Read (text.contains("Template: "))                                                                                          |
