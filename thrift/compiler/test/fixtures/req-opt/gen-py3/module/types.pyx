#
# Autogenerated by Thrift
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#  @generated
#

from libcpp.memory cimport shared_ptr, make_shared, unique_ptr, make_unique
from libcpp.string cimport string
from libcpp cimport bool as cbool
from libcpp.iterator cimport inserter as cinserter
from cpython cimport bool as pbool
from libc.stdint cimport int8_t, int16_t, int32_t, int64_t, uint32_t
from cython.operator cimport dereference as deref, preincrement as inc
import thrift.py3.types
cimport thrift.py3.types
cimport thrift.py3.exceptions
from thrift.py3.types import NOTSET
cimport thrift.py3.std_libcpp as std_libcpp
from thrift.py3.serializer cimport IOBuf
from thrift.py3.serializer import Protocol
cimport thrift.py3.serializer as serializer
from thrift.py3.serializer import deserialize, serialize

import sys
from collections.abc import Sequence, Set, Mapping, Iterable
from enum import Enum




cdef class Foo(thrift.py3.types.Struct):

    def __init__(
        Foo self,
        myInteger=None,
        myString=None,
        myBools=None,
        myNumbers=None
    ):
        self.c_Foo = make_shared[cFoo]()

        inst = self
        if myInteger is not None:
            deref(inst.c_Foo).myInteger = myInteger
        if myString is not None:
            deref(inst.c_Foo).myString = myString.encode('UTF-8')
            deref(inst.c_Foo).__isset.myString = True

        cdef List__bool _myBools
        if myBools is not None:
            _myBools = List__bool(myBools)
            deref(inst.c_Foo).myBools = deref(_myBools._vector)
            deref(inst.c_Foo).__isset.myBools = True

        cdef List__i32 _myNumbers
        if myNumbers is not None:
            _myNumbers = List__i32(myNumbers)
            deref(inst.c_Foo).myNumbers = deref(_myNumbers._vector)

    cdef bytes _serialize(Foo self, proto):
        cdef string c_str
        if proto is Protocol.COMPACT:
            serializer.CompactSerialize[cFoo](deref(self.c_Foo.get()), &c_str)
        elif proto is Protocol.BINARY:
            serializer.BinarySerialize[cFoo](deref(self.c_Foo.get()), &c_str)
        elif proto is Protocol.JSON:
            serializer.JSONSerialize[cFoo](deref(self.c_Foo.get()), &c_str)
        return <bytes> c_str

    cdef uint32_t _deserialize(Foo self, const IOBuf* buf, proto):
        cdef uint32_t needed
        if proto is Protocol.COMPACT:
            needed = serializer.CompactDeserialize[cFoo](buf, deref(self.c_Foo.get()))
        elif proto is Protocol.BINARY:
            needed = serializer.BinaryDeserialize[cFoo](buf, deref(self.c_Foo.get()))
        elif proto is Protocol.JSON:
            needed = serializer.JSONDeserialize[cFoo](buf, deref(self.c_Foo.get()))
        return needed

    def __reduce__(self):
        return (deserialize, (Foo, serialize(self)))

    def __call__(
        Foo self,
        myInteger=NOTSET,
        myString=NOTSET,
        myBools=NOTSET,
        myNumbers=NOTSET
    ):
        changes = any((
            myInteger is not NOTSET,

            myString is not NOTSET,

            myBools is not NOTSET,

            myNumbers is not NOTSET,
        ))

        if not changes:
            return self

        inst = <Foo>Foo.__new__(Foo)
        inst.c_Foo = make_shared[cFoo](deref(self.c_Foo))
        cdef Foo defaults = Foo_defaults

        # Convert None's to default value.
        if myInteger is None:
            deref(inst.c_Foo).myInteger = deref(defaults.c_Foo).myInteger
        if myInteger is NOTSET:
            myInteger = None
        if myString is None:
            deref(inst.c_Foo).myString = deref(defaults.c_Foo).myString
            deref(inst.c_Foo).__isset.myString = False
        if myString is NOTSET:
            myString = None
        if myBools is None:
            deref(inst.c_Foo).myBools = deref(defaults.c_Foo).myBools
            deref(inst.c_Foo).__isset.myBools = False
        if myBools is NOTSET:
            myBools = None
        if myNumbers is None:
            deref(inst.c_Foo).myNumbers = deref(defaults.c_Foo).myNumbers
        if myNumbers is NOTSET:
            myNumbers = None

        if myInteger is not None:
            deref(inst.c_Foo).myInteger = myInteger
        if myString is not None:
            deref(inst.c_Foo).myString = myString.encode('UTF-8')
            deref(inst.c_Foo).__isset.myString = True

        cdef List__bool _myBools
        if myBools is not None:
            _myBools = List__bool(myBools)
            deref(inst.c_Foo).myBools = deref(_myBools._vector)
            deref(inst.c_Foo).__isset.myBools = True

        cdef List__i32 _myNumbers
        if myNumbers is not None:
            _myNumbers = List__i32(myNumbers)
            deref(inst.c_Foo).myNumbers = deref(_myNumbers._vector)
        return inst

    def __iter__(self):
        yield 'myInteger', self.myInteger
        yield 'myString', self.myString
        yield 'myBools', self.myBools
        yield 'myNumbers', self.myNumbers

    def __bool__(self):
        return True or deref(self.c_Foo).__isset.myString or deref(self.c_Foo).__isset.myBools or True

    @staticmethod
    cdef create(shared_ptr[cFoo] c_Foo):
        inst = <Foo>Foo.__new__(Foo)
        inst.c_Foo = c_Foo
        return inst

    @property
    def myInteger(self):

        return self.c_Foo.get().myInteger

    @property
    def myString(self):
        if not deref(self.c_Foo).__isset.myString:
            return None

        return self.c_Foo.get().myString.decode('UTF-8')

    @property
    def myBools(self):
        if not deref(self.c_Foo).__isset.myBools:
            return None

        cdef shared_ptr[vector[cbool]] item
        if self.__myBools is None:
            item = make_shared[vector[cbool]](
                deref(self.c_Foo).myBools)
            self.__myBools = List__bool.create(item)
        return self.__myBools
        

    @property
    def myNumbers(self):

        cdef shared_ptr[vector[int32_t]] item
        if self.__myNumbers is None:
            item = make_shared[vector[int32_t]](
                deref(self.c_Foo).myNumbers)
            self.__myNumbers = List__i32.create(item)
        return self.__myNumbers
        


    def __richcmp__(self, other, op):
        cdef int cop = op
        if cop not in (2, 3):
            raise TypeError("unorderable types: {}, {}".format(self, other))
        if not (
                isinstance(self, Foo) and
                isinstance(other, Foo)):
            if cop == 2:  # different types are never equal
                return False
            else:         # different types are always notequal
                return True

        cdef cFoo cself = deref((<Foo>self).c_Foo)
        cdef cFoo cother = deref((<Foo>other).c_Foo)
        cdef cbool cmp = cself == cother
        if cop == 2:
            return cmp
        return not cmp

    def __hash__(Foo self):
        if not self.__hash:
            self.__hash = hash((
            self.myInteger,
            self.myString,
            self.myBools,
            self.myNumbers,
            ))
        return self.__hash

    def __repr__(Foo self):
        return f'Foo(myInteger={repr(self.myInteger)}, myString={repr(self.myString)}, myBools={repr(self.myBools)}, myNumbers={repr(self.myNumbers)})'


Foo_defaults = Foo()


cdef class List__bool:
    def __init__(self, items=None):
        if isinstance(items, List__bool):
            self._vector = (<List__bool> items)._vector
        else:
          self._vector = make_shared[vector[cbool]]()
          if items:
              for item in items:
                  deref(self._vector).push_back(item)

    @staticmethod
    cdef create(
            shared_ptr[vector[cbool]] c_items):
        inst = <List__bool>List__bool.__new__(List__bool)
        inst._vector = c_items
        return inst

    def __getitem__(self, int index):
        size = len(self)
        # Convert a negative index
        if index < 0:
            index = size - index
        if index >= size:
            raise IndexError('list index out of range')
        # Support negative indexes
        if index < 0:
            index = size - index
        cdef cbool citem = (
            deref(self._vector.get())[index])
        return citem

    def __len__(self):
        return deref(self._vector).size()

    def __richcmp__(self, other, op):
        cdef int cop = op
        if cop not in (2, 3):
            raise TypeError("unorderable types: {}, {}".format(type(self), type(other)))
        if not (isinstance(self, Iterable) and isinstance(other, Iterable)):
            return cop != 2
        if (len(self) != len(other)):
            return cop != 2

        for one, two in zip(self, other):
            if one != two:
                return cop != 2

        return cop == 2

    def __hash__(self):
        if not self.__hash:
            self.__hash = hash(tuple(self))
        return self.__hash

    def __contains__(self, item):
        if not self:
            return False
        cdef cbool citem = item
        cdef vector[cbool] vec = deref(
            self._vector.get())
        return std_libcpp.find(vec.begin(), vec.end(), citem) != vec.end()

    def __iter__(self):
        if not self:
            raise StopIteration
        cdef cbool citem
        for citem in deref(self._vector):
            yield citem

    def __repr__(self):
        if not self:
            return 'i[]'
        return f'i[{", ".join(map(repr, self))}]'

    def __reversed__(self):
        if not self:
            raise StopIteration
        cdef cbool citem
        cdef vector[cbool] vec = deref(
            self._vector.get())
        cdef vector[cbool].reverse_iterator loc = vec.rbegin()
        while loc != vec.rend():
            citem = deref(loc)
            yield citem
            inc(loc)

    def index(self, item):
        if not self:
            raise ValueError(f'{item} is not in list')
        cdef cbool citem = item
        cdef vector[cbool] vec = deref(self._vector.get())
        cdef vector[cbool].iterator loc = std_libcpp.find(vec.begin(), vec.end(), citem)
        if loc != vec.end():
            return <int64_t> std_libcpp.distance(vec.begin(), loc)
        raise ValueError(f'{item} is not in list')

    def count(self, item):
        if not self:
            return 0
        cdef cbool citem = item
        cdef vector[cbool] vec = deref(self._vector.get())
        return <int64_t> std_libcpp.count(vec.begin(), vec.end(), citem)


Sequence.register(List__bool)

cdef class List__i32:
    def __init__(self, items=None):
        if isinstance(items, List__i32):
            self._vector = (<List__i32> items)._vector
        else:
          self._vector = make_shared[vector[int32_t]]()
          if items:
              for item in items:
                  deref(self._vector).push_back(item)

    @staticmethod
    cdef create(
            shared_ptr[vector[int32_t]] c_items):
        inst = <List__i32>List__i32.__new__(List__i32)
        inst._vector = c_items
        return inst

    def __getitem__(self, int index):
        size = len(self)
        # Convert a negative index
        if index < 0:
            index = size - index
        if index >= size:
            raise IndexError('list index out of range')
        # Support negative indexes
        if index < 0:
            index = size - index
        cdef int32_t citem = (
            deref(self._vector.get())[index])
        return citem

    def __len__(self):
        return deref(self._vector).size()

    def __richcmp__(self, other, op):
        cdef int cop = op
        if cop not in (2, 3):
            raise TypeError("unorderable types: {}, {}".format(type(self), type(other)))
        if not (isinstance(self, Iterable) and isinstance(other, Iterable)):
            return cop != 2
        if (len(self) != len(other)):
            return cop != 2

        for one, two in zip(self, other):
            if one != two:
                return cop != 2

        return cop == 2

    def __hash__(self):
        if not self.__hash:
            self.__hash = hash(tuple(self))
        return self.__hash

    def __contains__(self, item):
        if not self:
            return False
        cdef int32_t citem = item
        cdef vector[int32_t] vec = deref(
            self._vector.get())
        return std_libcpp.find(vec.begin(), vec.end(), citem) != vec.end()

    def __iter__(self):
        if not self:
            raise StopIteration
        cdef int32_t citem
        for citem in deref(self._vector):
            yield citem

    def __repr__(self):
        if not self:
            return 'i[]'
        return f'i[{", ".join(map(repr, self))}]'

    def __reversed__(self):
        if not self:
            raise StopIteration
        cdef int32_t citem
        cdef vector[int32_t] vec = deref(
            self._vector.get())
        cdef vector[int32_t].reverse_iterator loc = vec.rbegin()
        while loc != vec.rend():
            citem = deref(loc)
            yield citem
            inc(loc)

    def index(self, item):
        if not self:
            raise ValueError(f'{item} is not in list')
        cdef int32_t citem = item
        cdef vector[int32_t] vec = deref(self._vector.get())
        cdef vector[int32_t].iterator loc = std_libcpp.find(vec.begin(), vec.end(), citem)
        if loc != vec.end():
            return <int64_t> std_libcpp.distance(vec.begin(), loc)
        raise ValueError(f'{item} is not in list')

    def count(self, item):
        if not self:
            return 0
        cdef int32_t citem = item
        cdef vector[int32_t] vec = deref(self._vector.get())
        return <int64_t> std_libcpp.count(vec.begin(), vec.end(), citem)


Sequence.register(List__i32)

