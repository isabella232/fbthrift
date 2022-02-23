# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import unittest

from thrift.py3lite.universal_name import (
    get_universal_hash,
    get_universal_hash_prefix,
    get_universal_hash_size,
    maybe_get_universal_hash_prefix,
    validate_universal_hash,
    validate_universal_hash_bytes,
    validate_universal_name,
    UniversalHashAlgorithm,
)


class UnionTests(unittest.TestCase):
    def test_validate_universal_name(self) -> None:
        validate_universal_name("foo.com/my/type")
        with self.assertRaises(ValueError):
            validate_universal_name("foo.com/my/type#1")

    def test_validate_universal_hash(self) -> None:
        validate_universal_hash(UniversalHashAlgorithm.Sha2_256, b"a" * 32, 8)
        with self.assertRaises(ValueError):
            validate_universal_hash(UniversalHashAlgorithm.Sha2_256, b"b" * 1, 8)
        with self.assertRaises(ValueError):
            validate_universal_hash(UniversalHashAlgorithm.Sha2_256, b"c" * 33, 8)

    def test_validate_universal_hash_bytes(self) -> None:
        validate_universal_hash_bytes(32, 8)
        with self.assertRaises(ValueError):
            validate_universal_hash_bytes(1, 8)

    def test_get_universal_hash_size(self) -> None:
        self.assertEquals(get_universal_hash_size(UniversalHashAlgorithm.Sha2_256), 32)

    def test_get_universal_hash(self) -> None:
        self.assertEquals(
            get_universal_hash(UniversalHashAlgorithm.Sha2_256, "foo.com/my/type"),
            b"\tat$\x9c\xef\xad\xb5\xea\rE;\xcb3\xadTv\x01\xfb\xfe\xc4\xb2\xd7\x95\x92N\xebg\xd4[\xe6F",
        )

    def test_get_universal_hash_prefix(self) -> None:
        self.assertEquals(get_universal_hash_prefix(b"a" * 32, 0), b"")
        self.assertEquals(get_universal_hash_prefix(b"b" * 32, 8), b"b" * 8)
        self.assertEquals(get_universal_hash_prefix(b"c" * 32, 32), b"c" * 32)
        self.assertEquals(get_universal_hash_prefix(b"d" * 32, 33), b"d" * 32)

    def test_maybe_get_universal_hash_prefix(self) -> None:
        self.assertEquals(
            len(
                maybe_get_universal_hash_prefix(
                    UniversalHashAlgorithm.Sha2_256, "a" * 24, 0
                )
            ),
            0,
        )
        self.assertEquals(
            len(
                maybe_get_universal_hash_prefix(
                    UniversalHashAlgorithm.Sha2_256, "a" * 24, 8
                )
            ),
            8,
        )
        self.assertEquals(
            len(
                maybe_get_universal_hash_prefix(
                    UniversalHashAlgorithm.Sha2_256, "a" * 24, 23
                )
            ),
            23,
        )
        self.assertEquals(
            len(
                maybe_get_universal_hash_prefix(
                    UniversalHashAlgorithm.Sha2_256, "a" * 24, 24
                )
            ),
            0,
        )
        self.assertEquals(
            len(
                maybe_get_universal_hash_prefix(
                    UniversalHashAlgorithm.Sha2_256, "a" * 48, 32
                )
            ),
            32,
        )
        self.assertEquals(
            len(
                maybe_get_universal_hash_prefix(
                    UniversalHashAlgorithm.Sha2_256, "a" * 48, 33
                )
            ),
            32,
        )
