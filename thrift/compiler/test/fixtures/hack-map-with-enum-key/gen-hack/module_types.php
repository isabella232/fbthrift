<?hh // strict
/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */

/**
 * Original thrift enum:-
 * FooEnum
 */
enum FooEnum: int {
  BAR = 0;
  BAZ = 1;
}

/**
 * Original thrift struct:-
 * BarStruct
 */
class BarStruct implements \IThriftStruct, \IThriftShapishStruct {
  use \ThriftSerializationTrait;

  const dict<int, this::TFieldSpec> SPEC = dict[
    1 => shape(
      'var' => 'e',
      'type' => \TType::MAP,
      'ktype' => \TType::I32,
      'vtype' => \TType::I32,
      'key' => shape(
        'type' => \TType::I32,
        'enum' => FooEnum::class,
      ),
      'val' => shape(
        'type' => \TType::I32,
        'enum' => FooEnum::class,
      ),
      'format' => 'collection',
    ),
    2 => shape(
      'var' => 's',
      'type' => \TType::SET,
      'etype' => \TType::I32,
      'elem' => shape(
        'type' => \TType::I32,
        'enum' => FooEnum::class,
      ),
      'format' => 'collection',
    ),
  ];
  const dict<string, int> FIELDMAP = dict[
    'e' => 1,
    's' => 2,
  ];

  const type TConstructorShape = shape(
    ?'e' => ?Map<FooEnum, FooEnum>,
    ?'s' => ?Set<FooEnum>,
  );

  const type TShape = shape(
    'e' => darray<FooEnum, FooEnum>,
    's' => darray<FooEnum, bool>,
    ...
  );
  const int STRUCTURAL_ID = 2986314503120154076;
  /**
   * Original thrift field:-
   * 1: map<enum module.FooEnum, enum module.FooEnum> e
   */
  public Map<FooEnum, FooEnum> $e;
  /**
   * Original thrift field:-
   * 2: set<enum module.FooEnum> s
   */
  public Set<FooEnum> $s;

  <<__Rx>>
  public function __construct(?Map<FooEnum, FooEnum> $e = null, ?Set<FooEnum> $s = null  ) {
    $this->e = $e ?? Map {};
    $this->s = $s ?? Set {};
  }

  <<__Rx>>
  public static function withDefaultValues(): this {
    return new static();
  }

  <<__Rx>>
  public static function fromShape(self::TConstructorShape $shape): this {
    return new static(
      Shapes::idx($shape, 'e'),
      Shapes::idx($shape, 's'),
    );
  }

  public function getName(): string {
    return 'BarStruct';
  }

  public static function getAllStructuredAnnotations(): \TStructAnnotations {
    return shape(
      'struct' => dict[],
      'fields' => dict[
      ],
    );
  }

  <<__Rx>>
  public static function __fromShape(self::TShape $shape): this {
    $me = new static();
    $me->e = (new Map($shape['e']));
    $me->s = new Set(Keyset\keys($shape['s']));
    return $me;
  }

  <<__Rx>>
  public function __toShape(): self::TShape {
    return shape(
      'e' => ThriftUtil::toDArray($this->e),
      's' => ThriftUtil::toDArray(Dict\fill_keys($this->s->toValuesArray(), true)),
    );
  }
}

