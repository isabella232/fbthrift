<?hh // strict
/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
class module_CONSTANTS implements \IThriftConstants {
  /**
   * Original thrift constant:-
   * i32 myInt
   */
  const int myInt = 1337;

  /**
   * Original thrift constant:-
   * string name
   */
  const string name = "Mark Zuckerberg";

  /**
   * Original thrift constant:-
   * string multi_line_string
   */
  const string multi_line_string = "This
is a
multi line string.
";

  /**
   * Original thrift constant:-
   * list<map<string, i32>> states
   */
  <<__Memoize>>
  public static function states(): ConstVector<ConstMap<string, int>>{
    return ImmVector {
      ImmMap {
        "San Diego" => 3211000,
        "Sacramento" => 479600,
        "SF" => 837400,
      },
      ImmMap {
        "New York" => 8406000,
        "Albany" => 98400,
      },
    };
  }

  /**
   * Original thrift constant:-
   * double x
   */
  const float x = 1.0;

  /**
   * Original thrift constant:-
   * double y
   */
  const float y = 1000000.0;

  /**
   * Original thrift constant:-
   * double z
   */
  const float z = 1e+09;

  /**
   * Original thrift constant:-
   * double zeroDoubleValue
   */
  const float zeroDoubleValue = 0.0;

  /**
   * Original thrift constant:-
   * double longDoubleValue
   */
  const float longDoubleValue = 2.59961e-05;

  /**
   * Original thrift constant:-
   * enum module.Company my_company
   */
  const Company my_company = Company::FACEBOOK;

  /**
   * Original thrift constant:-
   * string foo
   */
  const string foo = "foo";

  /**
   * Original thrift constant:-
   * i32 bar
   */
  const int bar = 42;

  /**
   * Original thrift constant:-
   * map<string, string> mymap
   */
  <<__Memoize>>
  public static function mymap(): ConstMap<string, string>{
    return ImmMap {
      "keys" => "values",
    };
  }

  /**
   * Original thrift constant:-
   * struct module.Internship instagram
   */
  <<__Memoize>>
  public static function instagram(): Internship{
    return Internship::fromShape(
      shape(
        "weeks" => 12,
        "title" => "Software Engineer",
        "employer" => Company::INSTAGRAM,
      )
    );
  }

  /**
   * Original thrift constant:-
   * struct module.Internship partial_const
   */
  <<__Memoize>>
  public static function partial_const(): Internship{
    return Internship::fromShape(
      shape(
        "weeks" => 8,
        "title" => "Some Job",
      )
    );
  }

  /**
   * Original thrift constant:-
   * list<struct module.Range> kRanges
   */
  <<__Memoize>>
  public static function kRanges(): ConstVector<Range>{
    return ImmVector {
      Range::fromShape(
        shape(
          "min" => 1,
          "max" => 2,
        )
      ),
      Range::fromShape(
        shape(
          "min" => 5,
          "max" => 6,
        )
      ),
    };
  }

  /**
   * Original thrift constant:-
   * list<struct module.Internship> internList
   */
  <<__Memoize>>
  public static function internList(): ConstVector<Internship>{
    return ImmVector {
      Internship::fromShape(
        shape(
          "weeks" => 12,
          "title" => "Software Engineer",
          "employer" => Company::INSTAGRAM,
        )
      ),
      Internship::fromShape(
        shape(
          "weeks" => 10,
          "title" => "Sales Intern",
          "employer" => Company::FACEBOOK,
        )
      ),
    };
  }

  /**
   * Original thrift constant:-
   * struct module.struct1 pod_0
   */
  <<__Memoize>>
  public static function pod_0(): struct1{
    return struct1::fromShape(
      shape(
      )
    );
  }

  /**
   * Original thrift constant:-
   * struct module.struct1 pod_s_0
   */
  <<__Memoize>>
  public static function pod_s_0(): struct1{
    return struct1::fromShape(
      shape(
      )
    );
  }

  /**
   * Original thrift constant:-
   * struct module.struct1 pod_1
   */
  <<__Memoize>>
  public static function pod_1(): struct1{
    return struct1::fromShape(
      shape(
        "a" => 10,
        "b" => "foo",
      )
    );
  }

  /**
   * Original thrift constant:-
   * struct module.struct1 pod_s_1
   */
  <<__Memoize>>
  public static function pod_s_1(): struct1{
    return struct1::fromShape(
      shape(
        "a" => 10,
        "b" => "foo",
      )
    );
  }

  /**
   * Original thrift constant:-
   * struct module.struct2 pod_2
   */
  <<__Memoize>>
  public static function pod_2(): struct2{
    return struct2::fromShape(
      shape(
        "a" => 98,
        "b" => "gaz",
        "c" => struct1::fromShape(
          shape(
            "a" => 12,
            "b" => "bar",
          )
        ),
        "d" => Vector {
          11,
          22,
          33,
        },
      )
    );
  }

  /**
   * Original thrift constant:-
   * struct module.struct2 pod_trailing_commas
   */
  <<__Memoize>>
  public static function pod_trailing_commas(): struct2{
    return struct2::fromShape(
      shape(
        "a" => 98,
        "b" => "gaz",
        "c" => struct1::fromShape(
          shape(
            "a" => 12,
            "b" => "bar",
          )
        ),
        "d" => Vector {
          11,
          22,
          33,
        },
      )
    );
  }

  /**
   * Original thrift constant:-
   * struct module.struct2 pod_s_2
   */
  <<__Memoize>>
  public static function pod_s_2(): struct2{
    return struct2::fromShape(
      shape(
        "a" => 98,
        "b" => "gaz",
        "c" => struct1::fromShape(
          shape(
            "a" => 12,
            "b" => "bar",
          )
        ),
        "d" => Vector {
          11,
          22,
          33,
        },
      )
    );
  }

  /**
   * Original thrift constant:-
   * struct module.struct3 pod_3
   */
  <<__Memoize>>
  public static function pod_3(): struct3{
    return struct3::fromShape(
      shape(
        "a" => "abc",
        "b" => 456,
        "c" => struct2::fromShape(
          shape(
            "a" => 888,
            "c" => struct1::fromShape(
              shape(
                "b" => "gaz",
              )
            ),
            "d" => Vector {
              1,
              2,
              3,
            },
          )
        ),
      )
    );
  }

  /**
   * Original thrift constant:-
   * struct module.struct3 pod_s_3
   */
  <<__Memoize>>
  public static function pod_s_3(): struct3{
    return struct3::fromShape(
      shape(
        "a" => "abc",
        "b" => 456,
        "c" => struct2::fromShape(
          shape(
            "a" => 888,
            "c" => struct1::fromShape(
              shape(
                "b" => "gaz",
              )
            ),
            "d" => Vector {
              1,
              2,
              3,
            },
          )
        ),
      )
    );
  }

  /**
   * Original thrift constant:-
   * struct module.struct4 pod_4
   */
  <<__Memoize>>
  public static function pod_4(): struct4{
    return struct4::fromShape(
      shape(
        "a" => 1234,
        "b" => 0.333,
        "c" => 25,
      )
    );
  }

  /**
   * Original thrift constant:-
   * struct module.union1 u_1_1
   */
  <<__Memoize>>
  public static function u_1_1(): union1{
    return union1::fromShape(
      shape(
        "i" => 97,
      )
    );
  }

  /**
   * Original thrift constant:-
   * struct module.union1 u_1_2
   */
  <<__Memoize>>
  public static function u_1_2(): union1{
    return union1::fromShape(
      shape(
        "d" => 5.6,
      )
    );
  }

  /**
   * Original thrift constant:-
   * struct module.union1 u_1_3
   */
  <<__Memoize>>
  public static function u_1_3(): union1{
    return union1::fromShape(
      shape(
      )
    );
  }

  /**
   * Original thrift constant:-
   * struct module.union2 u_2_1
   */
  <<__Memoize>>
  public static function u_2_1(): union2{
    return union2::fromShape(
      shape(
        "i" => 51,
      )
    );
  }

  /**
   * Original thrift constant:-
   * struct module.union2 u_2_2
   */
  <<__Memoize>>
  public static function u_2_2(): union2{
    return union2::fromShape(
      shape(
        "d" => 6.7,
      )
    );
  }

  /**
   * Original thrift constant:-
   * struct module.union2 u_2_3
   */
  <<__Memoize>>
  public static function u_2_3(): union2{
    return union2::fromShape(
      shape(
        "s" => struct1::fromShape(
          shape(
            "a" => 8,
            "b" => "abacabb",
          )
        ),
      )
    );
  }

  /**
   * Original thrift constant:-
   * struct module.union2 u_2_4
   */
  <<__Memoize>>
  public static function u_2_4(): union2{
    return union2::fromShape(
      shape(
        "u" => union1::fromShape(
          shape(
            "i" => 43,
          )
        ),
      )
    );
  }

  /**
   * Original thrift constant:-
   * struct module.union2 u_2_5
   */
  <<__Memoize>>
  public static function u_2_5(): union2{
    return union2::fromShape(
      shape(
        "u" => union1::fromShape(
          shape(
            "d" => 9.8,
          )
        ),
      )
    );
  }

  /**
   * Original thrift constant:-
   * struct module.union2 u_2_6
   */
  <<__Memoize>>
  public static function u_2_6(): union2{
    return union2::fromShape(
      shape(
        "u" => union1::fromShape(
          shape(
          )
        ),
      )
    );
  }

  /**
   * Original thrift constant:-
   * string apostrophe
   */
  const string apostrophe = "'";

  /**
   * Original thrift constant:-
   * string tripleApostrophe
   */
  const string tripleApostrophe = "'''";

  /**
   * Original thrift constant:-
   * string quotationMark
   */
  const string quotationMark = "\"";

  /**
   * Original thrift constant:-
   * string backslash
   */
  const string backslash = "\\";

  /**
   * Original thrift constant:-
   * string escaped_a
   */
  const string escaped_a = "\x61";

  /**
   * Original thrift constant:-
   * map<string, i32> char2ascii
   */
  <<__Memoize>>
  public static function char2ascii(): ConstMap<string, int>{
    return ImmMap {
      "'" => 39,
      "\"" => 34,
      "\\" => 92,
      "\x61" => 97,
    };
  }

  /**
   * Original thrift constant:-
   * list<string> escaped_strings
   */
  <<__Memoize>>
  public static function escaped_strings(): ConstVector<string>{
    return ImmVector {
      "\x61",
      "\xab",
      "\x6a",
      "\xa6",
      "\x61yyy",
      "\xabyyy",
      "\x6ayyy",
      "\xa6yyy",
      "zzz\x61",
      "zzz\xab",
      "zzz\x6a",
      "zzz\xa6",
      "zzz\x61yyy",
      "zzz\xabyyy",
      "zzz\x6ayyy",
      "zzz\xa6yyy",
    };
  }

  /**
   * Original thrift constant:-
   * bool false_c
   */
  const bool false_c = false;

  /**
   * Original thrift constant:-
   * bool true_c
   */
  const bool true_c = true;

  /**
   * Original thrift constant:-
   * byte zero_byte
   */
  const int zero_byte = 0;

  /**
   * Original thrift constant:-
   * i16 zero16
   */
  const int zero16 = 0;

  /**
   * Original thrift constant:-
   * i32 zero32
   */
  const int zero32 = 0;

  /**
   * Original thrift constant:-
   * i64 zero64
   */
  const int zero64 = 0;

  /**
   * Original thrift constant:-
   * double zero_dot_zero
   */
  const float zero_dot_zero = 0.0;

  /**
   * Original thrift constant:-
   * string empty_string
   */
  const string empty_string = "";

  /**
   * Original thrift constant:-
   * list<i32> empty_int_list
   */
  <<__Memoize>>
  public static function empty_int_list(): ConstVector<int>{
    return ImmVector {
    };
  }

  /**
   * Original thrift constant:-
   * list<string> empty_string_list
   */
  <<__Memoize>>
  public static function empty_string_list(): ConstVector<string>{
    return ImmVector {
    };
  }

  /**
   * Original thrift constant:-
   * set<i32> empty_int_set
   */
  <<__Memoize>>
  public static function empty_int_set(): ConstSet<int>{
    return ImmSet {
    };
  }

  /**
   * Original thrift constant:-
   * set<string> empty_string_set
   */
  <<__Memoize>>
  public static function empty_string_set(): ConstSet<string>{
    return ImmSet {
    };
  }

  /**
   * Original thrift constant:-
   * map<i32, i32> empty_int_int_map
   */
  <<__Memoize>>
  public static function empty_int_int_map(): ConstMap<int, int>{
    return ImmMap {
    };
  }

  /**
   * Original thrift constant:-
   * map<i32, string> empty_int_string_map
   */
  <<__Memoize>>
  public static function empty_int_string_map(): ConstMap<int, string>{
    return ImmMap {
    };
  }

  /**
   * Original thrift constant:-
   * map<string, i32> empty_string_int_map
   */
  <<__Memoize>>
  public static function empty_string_int_map(): ConstMap<string, int>{
    return ImmMap {
    };
  }

  /**
   * Original thrift constant:-
   * map<string, string> empty_string_string_map
   */
  <<__Memoize>>
  public static function empty_string_string_map(): ConstMap<string, string>{
    return ImmMap {
    };
  }


  public static function getAllStructuredAnnotations(): dict<string, dict<string, \IThriftStruct>> {
    return dict[
    ];
  }
}

