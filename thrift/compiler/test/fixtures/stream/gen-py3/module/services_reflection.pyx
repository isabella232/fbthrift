#
# Autogenerated by Thrift
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#  @generated
#

from thrift.py3.reflection cimport (
  MethodSpec as __MethodSpec,
  ArgumentSpec as __ArgumentSpec,
  NumberType as __NumberType,
)

import folly.iobuf as _fbthrift_iobuf


cimport module.types as _module_types


cdef __InterfaceSpec get_reflection__PubSubStreamingService(bint for_clients):
    cdef __InterfaceSpec spec = __InterfaceSpec._fbthrift_create(
        name="PubSubStreamingService",
        annotations={
        },
    )
    spec.add_method(
        __MethodSpec._fbthrift_create(
            name="returnstream",
            arguments=(
                __ArgumentSpec._fbthrift_create(
                    name="i32_from",
                    type=int,
                    kind=__NumberType.I32,
                    annotations={
                    },
                ),
                __ArgumentSpec._fbthrift_create(
                    name="i32_to",
                    type=int,
                    kind=__NumberType.I32,
                    annotations={
                    },
                ),
            ),
            result=_module_types.ClientBufferedStream__i32 if for_clients else _module_types.ServerStream__i32,
            result_kind=__NumberType.NOT_A_NUMBER,
            exceptions=(
            ),
            annotations={
            },
        )
    )
    spec.add_method(
        __MethodSpec._fbthrift_create(
            name="streamthrows",
            arguments=(
                __ArgumentSpec._fbthrift_create(
                    name="foo",
                    type=int,
                    kind=__NumberType.I32,
                    annotations={
                    },
                ),
            ),
            result=_module_types.ClientBufferedStream__i32 if for_clients else _module_types.ServerStream__i32,
            result_kind=__NumberType.NOT_A_NUMBER,
            exceptions=(
            ),
            annotations={
            },
        )
    )
    spec.add_method(
        __MethodSpec._fbthrift_create(
            name="boththrows",
            arguments=(
                __ArgumentSpec._fbthrift_create(
                    name="foo",
                    type=int,
                    kind=__NumberType.I32,
                    annotations={
                    },
                ),
            ),
            result=_module_types.ClientBufferedStream__i32 if for_clients else _module_types.ServerStream__i32,
            result_kind=__NumberType.NOT_A_NUMBER,
            exceptions=(
                _module_types.FooEx,
            ),
            annotations={
            },
        )
    )
    spec.add_method(
        __MethodSpec._fbthrift_create(
            name="responseandstreamthrows",
            arguments=(
                __ArgumentSpec._fbthrift_create(
                    name="foo",
                    type=int,
                    kind=__NumberType.I32,
                    annotations={
                    },
                ),
            ),
            result=_module_types.ResponseAndClientBufferedStream__i32_i32 if for_clients else _module_types.ResponseAndServerStream__i32_i32,
            result_kind=__NumberType.NOT_A_NUMBER,
            exceptions=(
                _module_types.FooEx,
            ),
            annotations={
            },
        )
    )
    spec.add_method(
        __MethodSpec._fbthrift_create(
            name="returnstreamFast",
            arguments=(
                __ArgumentSpec._fbthrift_create(
                    name="i32_from",
                    type=int,
                    kind=__NumberType.I32,
                    annotations={
                    },
                ),
                __ArgumentSpec._fbthrift_create(
                    name="i32_to",
                    type=int,
                    kind=__NumberType.I32,
                    annotations={
                    },
                ),
            ),
            result=_module_types.ClientBufferedStream__i32 if for_clients else _module_types.ServerStream__i32,
            result_kind=__NumberType.NOT_A_NUMBER,
            exceptions=(
            ),
            annotations={
                """thread""": """eb""",            },
        )
    )
    return spec
