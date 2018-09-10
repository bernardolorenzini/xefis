/* vim:ts=4
 *
 * Copyleft 2012…2016  Michał Gawron
 * Marduk Unix Labs, http://mulabs.org/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Visit http://www.gnu.org/licenses/gpl-3.0.html for more information on licensing.
 */

#ifndef XEFIS__MODULES__INSTRUMENTS__DATATABLE_H__INCLUDED
#define XEFIS__MODULES__INSTRUMENTS__DATATABLE_H__INCLUDED

// Standard:
#include <cstddef>
#include <optional>

// Qt:
#include <QtWidgets/QWidget>
#include <QtXml/QDomElement>

// Xefis:
#include <xefis/config/all.h>
#include <xefis/core/instrument.h>
#include <xefis/core/module_io.h>
#include <xefis/core/property.h>
#include <xefis/core/property_observer.h>
#include <xefis/core/xefis.h>
#include <xefis/support/instrument/instrument_support.h>


class Datatable:
	public xf::Instrument<xf::ModuleIO>,
	private xf::InstrumentSupport
{
	class Line
	{
	  public:
		// Ctor
		explicit
		Line (std::string_view const& label, xf::BasicProperty const&);

		// Ctor
		explicit
		Line (std::string_view const& label, xf::BasicProperty const&,
			  QColor label_and_value_color);

		// Ctor
		explicit
		Line (std::string_view const& label, xf::BasicProperty const&,
			  std::optional<QColor> label_color,
			  std::optional<QColor> value_color);

		/**
		 * Return value to be painted.
		 */
		QString
		stringify() const;

	  public:
		std::string					label;
		QColor						label_color	{ Qt::white };
		QColor						value_color	{ Qt::white };
		xf::BasicProperty const&	property;
	};

  public:
	// Ctor
	explicit
	Datatable (xf::Xefis*, std::string_view const& instance = {});

	/**
	 * Set font size for all labels.
	 */
	void
	set_label_font_size (float);

	/**
	 * Set font size for all values.
	 */
	void
	set_value_font_size (float);

	/**
	 * Set table alignment within widget.
	 */
	void
	set_alignment (Qt::Alignment);

	/**
	 * Add text line to the table.
	 * Forwards arguments to the Line constructor.
	 */
	template<class ...Arg>
		void
		add_line (Arg&& ...args);

	// Module API
	void
	process (xf::Cycle const&) override;

	// Instrument API
	void
	paint (xf::PaintRequest&) const override;

  private:
	float					_label_font_size	{ 16.0 };
	float					_value_font_size	{ 18.0 };
	Qt::Alignment			_alignment			{ Qt::AlignTop };
	std::vector<Line>		_list;
	xf::PropertyObserver	_inputs_observer;
};


template<class ...Arg>
	void
	Datatable::add_line (Arg&& ...args)
	{
		_list.emplace_back (std::forward<Arg> (args)...);
	}

#endif
