/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */

package test.fixtures.exceptions;

import java.util.*;

public class RaiserReactiveAsyncWrapper 
  implements Raiser.Async {
  private Raiser.Reactive _delegate;

  public RaiserReactiveAsyncWrapper(Raiser.Reactive _delegate) {
    
    this._delegate = _delegate;
  }

  public RaiserReactiveAsyncWrapper(org.apache.thrift.ProtocolId _protocolId, reactor.core.publisher.Mono<? extends com.facebook.thrift.client.RpcClient> _rpcClient, Map<String, String> _headers, Map<String, String> _persistentHeaders) {
    this(new RaiserReactiveClient(_protocolId, _rpcClient, _headers, _persistentHeaders));
  }

  @java.lang.Override
  public void close() {
    _delegate.dispose();
  }

  @java.lang.Override
  public com.google.common.util.concurrent.ListenableFuture<Void> doBland() {
      return com.facebook.thrift.util.FutureUtil.toListenableFuture(_delegate.doBland());
  }

  @java.lang.Override
  public com.google.common.util.concurrent.ListenableFuture<Void> doBland(
    com.facebook.thrift.client.RpcOptions rpcOptions) {
      return com.facebook.thrift.util.FutureUtil.toListenableFuture(_delegate.doBland( rpcOptions));
  }

  @java.lang.Override
  public com.google.common.util.concurrent.ListenableFuture<com.facebook.thrift.client.ResponseWrapper<Void>> doBlandWrapper(
    com.facebook.thrift.client.RpcOptions rpcOptions) {
    return com.facebook.thrift.util.FutureUtil.toListenableFuture(_delegate.doBlandWrapper( rpcOptions));
  }

  @java.lang.Override
  public com.google.common.util.concurrent.ListenableFuture<Void> doRaise() {
      return com.facebook.thrift.util.FutureUtil.toListenableFuture(_delegate.doRaise());
  }

  @java.lang.Override
  public com.google.common.util.concurrent.ListenableFuture<Void> doRaise(
    com.facebook.thrift.client.RpcOptions rpcOptions) {
      return com.facebook.thrift.util.FutureUtil.toListenableFuture(_delegate.doRaise( rpcOptions));
  }

  @java.lang.Override
  public com.google.common.util.concurrent.ListenableFuture<com.facebook.thrift.client.ResponseWrapper<Void>> doRaiseWrapper(
    com.facebook.thrift.client.RpcOptions rpcOptions) {
    return com.facebook.thrift.util.FutureUtil.toListenableFuture(_delegate.doRaiseWrapper( rpcOptions));
  }

  @java.lang.Override
  public com.google.common.util.concurrent.ListenableFuture<String> get200() {
      return com.facebook.thrift.util.FutureUtil.toListenableFuture(_delegate.get200());
  }

  @java.lang.Override
  public com.google.common.util.concurrent.ListenableFuture<String> get200(
    com.facebook.thrift.client.RpcOptions rpcOptions) {
      return com.facebook.thrift.util.FutureUtil.toListenableFuture(_delegate.get200( rpcOptions));
  }

  @java.lang.Override
  public com.google.common.util.concurrent.ListenableFuture<com.facebook.thrift.client.ResponseWrapper<String>> get200Wrapper(
    com.facebook.thrift.client.RpcOptions rpcOptions) {
    return com.facebook.thrift.util.FutureUtil.toListenableFuture(_delegate.get200Wrapper( rpcOptions));
  }

  @java.lang.Override
  public com.google.common.util.concurrent.ListenableFuture<String> get500() {
      return com.facebook.thrift.util.FutureUtil.toListenableFuture(_delegate.get500());
  }

  @java.lang.Override
  public com.google.common.util.concurrent.ListenableFuture<String> get500(
    com.facebook.thrift.client.RpcOptions rpcOptions) {
      return com.facebook.thrift.util.FutureUtil.toListenableFuture(_delegate.get500( rpcOptions));
  }

  @java.lang.Override
  public com.google.common.util.concurrent.ListenableFuture<com.facebook.thrift.client.ResponseWrapper<String>> get500Wrapper(
    com.facebook.thrift.client.RpcOptions rpcOptions) {
    return com.facebook.thrift.util.FutureUtil.toListenableFuture(_delegate.get500Wrapper( rpcOptions));
  }

}