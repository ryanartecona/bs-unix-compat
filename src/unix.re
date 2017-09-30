type error =
  | E2BIG
  | EACCES
  | EAGAIN
  | EBADF
  | EBUSY
  | ECHILD
  | EDEADLK
  | EDOM
  | EEXIST
  | EFAULT
  | EFBIG
  | EINTR
  | EINVAL
  | EIO
  | EISDIR
  | EMFILE
  | EMLINK
  | ENAMETOOLONG
  | ENFILE
  | ENODEV
  | ENOENT
  | ENOEXEC
  | ENOLCK
  | ENOMEM
  | ENOSPC
  | ENOSYS
  | ENOTDIR
  | ENOTEMPTY
  | ENOTTY
  | ENXIO
  | EPERM
  | EPIPE
  | ERANGE
  | EROFS
  | ESPIPE
  | ESRCH
  | EXDEV
  | EWOULDBLOCK
  | EINPROGRESS
  | EALREADY
  | ENOTSOCK
  | EDESTADDRREQ
  | EMSGSIZE
  | EPROTOTYPE
  | ENOPROTOOPT
  | EPROTONOSUPPORT
  | ESOCKTNOSUPPORT
  | EOPNOTSUPP
  | EPFNOSUPPORT
  | EAFNOSUPPORT
  | EADDRINUSE
  | EADDRNOTAVAIL
  | ENETDOWN
  | ENETUNREACH
  | ENETRESET
  | ECONNABORTED
  | ECONNRESET
  | ENOBUFS
  | EISCONN
  | ENOTCONN
  | ESHUTDOWN
  | ETOOMANYREFS
  | ETIMEDOUT
  | ECONNREFUSED
  | EHOSTDOWN
  | EHOSTUNREACH
  | ELOOP
  | EOVERFLOW
  | EUNKNOWNERR int;

exception Unix_error error string string;

module Node = {
  type fd = int;
  external isatty : fd => Js.boolean = "" [@@bs.module "tty"];
};

type file_descr = ref int;

type out_channel = {
  mutable buffer: string,
  output: out_channel => string => unit
};

external cast_oc : Pervasives.out_channel => out_channel = "%identity";

let js_ref_eq (a: 'a) (b: 'a) :Js.boolean =>
  [%bs.raw {| function (a, b) {return a === b;} |}] a b;

let descr_of_out_channel (oc: Pervasives.out_channel) :file_descr =>
  if (Js.to_bool @@ js_ref_eq oc Pervasives.stdout) {
    ref 1
  } else if (
    Js.to_bool @@ js_ref_eq oc Pervasives.stderr
  ) {
    ref 2
  } else {
    failwith "unknown out_channel"
  };

let isatty (fd: file_descr) :bool => Js.to_bool (Node.isatty !fd);
