/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */

package test.fixtures.basicannotations;

import java.util.*;

public class MyServicePrioChildReactiveBlockingWrapper  extends test.fixtures.basicannotations.MyServicePrioParentReactiveBlockingWrapper
  implements MyServicePrioChild {
  private final MyServicePrioChild.Reactive _delegate;

  public MyServicePrioChildReactiveBlockingWrapper(MyServicePrioChild.Reactive _delegate) {
    super(_delegate);
    this._delegate = _delegate;
  }

  @java.lang.Override
  public void close() {
    _delegate.close();
  }

  @java.lang.Override
  public void pang() throws org.apache.thrift.TException {
      _delegate.pang().block();
  }

}