#include "proto/addressbook.pb.h"
#include "measure_time.h"
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
#include <google/protobuf/port_def.inc>

const char* _InternalParse22(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // .tutorial.Header header = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          // ptr = ctx->ParseMessage(_internal_mutable_header(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // repeated .tutorial.Person people = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr -= 1;
          do {
            ptr += 1;
            // ptr = ctx->ParseMessage(_internal_add_people(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<18>(ptr));
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        // ptr = UnknownFieldParse(tag,
        //     _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        //     ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}
bool MergeFromImpl222(::PROTOBUF_NAMESPACE_ID::io::ZeroCopyInputStream *input, ::PROTOBUF_NAMESPACE_ID::MessageLite *msg,
                      ::PROTOBUF_NAMESPACE_ID::MessageLite::ParseFlags parse_flags)
{
  using namespace ::PROTOBUF_NAMESPACE_ID;
  const char *ptr;
  internal::ParseContext ctx(io::CodedInputStream::GetDefaultRecursionLimit(),
                             true, &ptr, input);
  ptr = msg->_InternalParse(ptr, &ctx);
  // ctx has no explicit limit (hence we end on end of stream)
  if (PROTOBUF_PREDICT_TRUE(ptr && ctx.EndedAtEndOfStream()))
  {
    return true;
  }
  return false;
}

int TestDeserilization()
{
  using namespace google::protobuf;

  tutorial::Person p1;
  p1.set_name("xiaoming");

  tutorial::AddressBook b1;
  b1.mutable_header()->set_t0(100);
  for (int i = 0; i < 2; ++i)
  {
    *b1.mutable_people()->Add() = p1;
  }

  std::string s1;
  b1.SerializeToString(&s1);

  tutorial::AddressBook b2;
  b2.ParseFromString(s1);
  // MEASURE_TIME(&MessageLite::ParsePartialFromString, &b2, s1);

  // 创建一个包含序列化消息的字符串
  std::string serialized_data = s1;
  // 创建一个包含序列化消息的字符串

  // 创建一个内存输入流
  google::protobuf::io::ArrayInputStream input_stream(serialized_data.data(), serialized_data.size());

  // 创建一个 CodedInputStream 对象，使用内存输入流作为输入
  google::protobuf::io::CodedInputStream coded_input_stream(&input_stream);

  // 创建一个 AddressBook 实例，用于存储反序列化后的消息
  tutorial::AddressBook parsed_address_book;

  // 读取标记并解析消息字段
  while (!coded_input_stream.ExpectAtEnd())
  {
    // 读取下一个标记
    uint32_t tag;
    if (!coded_input_stream.ReadVarint32(&tag))
    {
      std::cerr << "Failed to read tag" << std::endl;
      return 1;
    }

    if ((tag >> 3) == 1)
    {
      tutorial::Header header;
      if (!header.ParseFromCodedStream(&coded_input_stream))
      {
        std::cerr << "Failed to parse Header field" << std::endl;
        return 1;
      }
      parsed_address_book.mutable_header()->CopyFrom(header);
      break;
    }
    else
    {
      if (!coded_input_stream.Skip(tag & 0x7))
      {
        std::cerr << "Failed to skip field with tag " << tag << std::endl;
        return 1;
      }
    }
  }

  // 打印解析后的消息内容
  std::cout << "Parsed AddressBook: " << parsed_address_book.DebugString() << std::endl;

  return 0;
}