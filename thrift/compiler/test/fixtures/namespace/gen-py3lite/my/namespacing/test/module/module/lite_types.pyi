#
# Autogenerated by Thrift
#
# DO NOT EDIT
#  @generated
#

import typing as _typing

import thrift.py3lite.types as _fbthrift_py3lite_types
import thrift.py3lite.exceptions as _fbthrift_py3lite_exceptions


class Foo(_fbthrift_py3lite_types.Struct):
    MyInt: _typing.Final[int] = ...
    def __init__(
        self, *,
        MyInt: _typing.Optional[int]=...
    ) -> None: ...

    def __call__(
        self, *,
        MyInt: _typing.Optional[int]=...
    ) -> Foo: ...
    def __iter__(self) -> _typing.Iterator[_typing.Tuple[str, _typing.Union[int]]]: ...


class _fbthrift_TestService_init_args(_fbthrift_py3lite_types.Struct):
    int1: _typing.Final[int] = ...

    def __init__(
        self, *,
        int1: _typing.Optional[int]=...
    ) -> None: ...

    def __iter__(self) -> _typing.Iterator[_typing.Tuple[
        str,
        _typing.Union[None, int]]]: ...

class _fbthrift_TestService_init_result(_fbthrift_py3lite_types.Struct):
    success: _typing.Final[int]

    def __init__(
        self, *, success: _typing.Optional[int] = ...
    ) -> None: ...

    def __iter__(self) -> _typing.Iterator[_typing.Tuple[
        str,
        _typing.Union[
            int,
        ]]]: ...


