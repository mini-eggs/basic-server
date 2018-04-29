;;;; basic-server.lisp

(in-package #:basic-server)

(defparameter *dir* (merge-pathnames "c/main" (asdf:system-source-directory :basic-server)))

(define-foreign-library c-server
  (t (:default (namestring *dir*))))
(use-foreign-library c-server)

(defun handle (req)
  (declare (ignore req))
  "Hello, world!")

(defun start (&optional (port 8080) (maxbuf 1014))
  (format t "~%Server has been started on port ~A.~%" port)
  (defcallback inner-handle :string () (handle "todo"))
  (foreign-funcall "start" :int port :int maxbuf :pointer (callback inner-handle)))

(start 5016)
