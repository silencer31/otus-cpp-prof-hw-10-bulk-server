#pragma once

#include "console.h"
#include "file_logger.h"

#include <memory>

/**
* @brief ����� - ���������� ����������� ������ �� �������.
*/
class Interpreter {
public:
	Interpreter() = delete;
	
	explicit Interpreter(const std::size_t& bulk_size, const std::uint32_t& handle_id,
		const std::shared_ptr<IWriter>& io_ptr, const std::shared_ptr<IWriter>& iw_ptr,
		const std::shared_ptr<IGatherer>& ig_ptr)
	{
		collector_ptr = std::make_shared<Collector>(bulk_size, handle_id, ig_ptr);

		// ������� Console � �������� ��� ��������� �� ��������� � �������.
		console_ptr = std::make_shared<Console>(collector_ptr, io_ptr);
		
		// ������� File Logger � �������� ��� ��������� �� ��������� � �������.
		file_logger_ptr = std::make_shared<FileLogger>(collector_ptr, iw_ptr);

		// � ��������� � ������� ��������� Console ��� ������������.
		collector_ptr->attach(console_ptr);

		// � ��������� � ������� ��������� File Logger ��� ������������.
		collector_ptr->attach(file_logger_ptr);
	}
	
	~Interpreter() {
		collector_ptr->detach(console_ptr);
		collector_ptr->detach(file_logger_ptr);
	}

	/**
	* ��������� �������� ������.
	* @param command �������� ������
	*/
	void handle_input(const std::string& command);

	/**
	* ��������� ����������� EOF.
	*/
	void handle_eof();

private:
	std::shared_ptr<Collector>  collector_ptr;	 // ��������� �� ������ � ���������� � �������.
	
	std::shared_ptr<FileLogger> file_logger_ptr; // ��������� �� ������ ��� ������ ��������� ������ � ����.
	std::shared_ptr<Console>	console_ptr;	 // ��������� �� ������ ��� ������ ��������� ������ � �������.
};