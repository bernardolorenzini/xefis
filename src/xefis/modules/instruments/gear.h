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

#ifndef XEFIS__MODULES__INSTRUMENTS__GEAR_H__INCLUDED
#define XEFIS__MODULES__INSTRUMENTS__GEAR_H__INCLUDED

// Standard:
#include <cstddef>

// Xefis:
#include <xefis/config/all.h>
#include <xefis/core/v2/instrument.h>
#include <xefis/core/instrument_aids.h>
#include <xefis/core/v2/property.h>
#include <xefis/core/v2/property_observer.h>


class GearIO: public v2::ModuleIO
{
  public:
	/*
	 * Input
	 */

	v2::PropertyIn<bool>	requested_down	{ this, "/requested-down" };
	v2::PropertyIn<bool>	nose_up			{ this, "/nose-up" };
	v2::PropertyIn<bool>	nose_down		{ this, "/nose-down" };
	v2::PropertyIn<bool>	left_up			{ this, "/left-up" };
	v2::PropertyIn<bool>	left_down		{ this, "/left-down" };
	v2::PropertyIn<bool>	right_up		{ this, "/right-up" };
	v2::PropertyIn<bool>	right_down		{ this, "/right-down" };
};


class Gear:
	public v2::Instrument<GearIO>,
	protected xf::InstrumentAids
{
  public:
	// Ctor
	explicit
	Gear (std::unique_ptr<GearIO>, std::string const& instance = {});

	// Module API
	void
	process (xf::Cycle const&) override;

  protected:
	// QWidget API
	void
	resizeEvent (QResizeEvent*) override;

	// QWidget API
	void
	paintEvent (QPaintEvent*) override;

  private:
	v2::PropertyObserver	_inputs_observer;
};

#endif
